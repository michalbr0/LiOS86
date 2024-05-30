#include <cstddef>

#include "../ata.hpp"
#include "../bpb.hpp"
#include "../directory_sector.hpp"
#include "../mbr.hpp"
#include "../utils/data_manipulation.hpp"
#include "../xstd/expected.hpp"

namespace LiOS86 {

    enum class FileSearchError { NOT_FOUND, BAD_CLUSTER_CHAIN };
    static auto getFileStartingCluster(
        const char* shortFilename, 
        uint32_t parentDirectoryStartingCluster, 
        volatile uint8_t* fatPtr,
        auto clusterNumberToSectorNumber,
        uint8_t sectorsPerCluster
    ) -> xstd::expected<uint32_t, FileSearchError> {

        uint32_t currentCluster = parentDirectoryStartingCluster;

        do {
            auto currentSectorNumber = clusterNumberToSectorNumber(currentCluster);
            for(int i = 0; i < sectorsPerCluster; ++i) {
                const auto directorySector = LiOS86::DirectorySectorHandle(currentSectorNumber + i);
                for(const auto entry : directorySector) {
                    const auto sfn = entry.getShortFileName();
                    if(sfn == shortFilename) {
                        return entry.getFirstClusterNumber();
                    }
                }
            }
            currentCluster = LiOS86::readFromMemoryAndPun<uint32_t>(fatPtr, currentCluster * 4);
        } while(currentCluster > 0x00000001 && currentCluster < 0x0FFFFFF7);

        if(currentCluster >= 0x0FFFFFF8 && currentCluster <= 0x0FFFFFFF) {
            return xstd::unexpected(FileSearchError::NOT_FOUND);
        }
        return xstd::unexpected(FileSearchError::BAD_CLUSTER_CHAIN);
    }

    static auto copyFileToMemory(
        uint32_t fileStartingCluster, 
        volatile uint8_t* destinationPtr, 
        volatile uint8_t* fatPtr, 
        auto clusterNumberToSectorNumber,
        uint8_t sectorsPerCluster, 
        uint16_t bytesPerSector
    ) -> void {

        auto currentCluster = fileStartingCluster;
        uint32_t currentClusterCount = 0;

        do {
            auto currentSectorNumber = clusterNumberToSectorNumber(currentCluster);
            for(int i = 0; i < sectorsPerCluster; ++i) {
                const auto sector = LiOS86::readSectors(currentSectorNumber + i, 1);
                if(!sector) {
                    // panic
                    while(true) { }
                }
                const auto currentSectorCount = sectorsPerCluster * currentClusterCount + i;
                for(int j = 0; j < 512; ++j) {
                    destinationPtr[currentSectorCount * bytesPerSector + j] = (*sector)[j];
                }
            }
            currentCluster = LiOS86::readFromMemoryAndPun<uint32_t>(fatPtr, currentCluster * 4);
            ++currentClusterCount;
        } while(currentCluster > 0x00000001 && currentCluster < 0x0FFFFFF7);

        // TODO error handling
    }

}

extern "C" constexpr auto KERNEL_MEMORY_START_ADDRESS = 0x01000000;

extern "C" void kloader() {
    
    const auto mbrHandle = LiOS86::MBRHandle();
    const auto activePartitionEntryHandle = mbrHandle.getActivePartitionTableEntryHandle();
    const auto partitionStartingSector = activePartitionEntryHandle.getStartSector();

    const auto bpbHandle = LiOS86::BPBHandle(partitionStartingSector);
    const auto bytesPerSector = bpbHandle.getBytesPerSector();
    // assert bytesPerSector == 512
    const auto sectorsPerCluster = bpbHandle.getSectorsPerCluster();
    const auto FATSizeInSectors = bpbHandle.getFATSizeInSectors();
    const auto rootDirectoryStartingCluster = bpbHandle.getRootDirectoryStartingCluster();

    const auto FATStartingSector = partitionStartingSector + bpbHandle.getFirstActiveFATOffsetInSectors();

    static constexpr auto EXTENDED_MEMORY_START_ADDRESS = 0x00100000;
    auto extendedMemoryPtr = reinterpret_cast<volatile uint8_t*>(EXTENDED_MEMORY_START_ADDRESS);

    for(std::size_t i = 0; i < FATSizeInSectors; ++i) {
        const auto sector = LiOS86::readSectors(FATStartingSector + i, 1);
        if(!sector) {
            // panic
            while(true) { }
        }
        for(int j = 0; j < 512; ++j) {
            extendedMemoryPtr[i * 512 + j] = (*sector)[j];
        }
    }

    const auto dataSectionStartingSector = partitionStartingSector + bpbHandle.getDataSectionOffsetInSectors();
    const auto clusterNumberToSectorNumber = [dataSectionStartingSector, sectorsPerCluster](std::size_t clusterNumber) {
        return dataSectionStartingSector + (clusterNumber - 2) * sectorsPerCluster;
    };

    const auto kernelFileStartingCluster = 
        LiOS86::getFileStartingCluster("KERNEL  BIN", 
                                        rootDirectoryStartingCluster, 
                                        extendedMemoryPtr,
                                        clusterNumberToSectorNumber,
                                        sectorsPerCluster
                                        );
    
    if(!kernelFileStartingCluster) {
        // panic
        while(true) { }
    }

    auto kernelMemoryPtr = reinterpret_cast<volatile uint8_t*>(KERNEL_MEMORY_START_ADDRESS);

    LiOS86::copyFileToMemory(*kernelFileStartingCluster,
                                kernelMemoryPtr,
                                extendedMemoryPtr,
                                clusterNumberToSectorNumber,
                                sectorsPerCluster,
                                bytesPerSector
                            );

}
