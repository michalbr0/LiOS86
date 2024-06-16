#pragma once

#include <cstddef>

#include "utils/data_manipulation.hpp"
#include "utils/disk_buffer.hpp"
#include "xstd/array.hpp"
#include "xstd/cstring.hpp"

namespace LiOS86 {
    
    class DirectorySectorHandle : ReadonlyDiskBuffer<1> {
        public:
            explicit DirectorySectorHandle(std::size_t startingSectorNumber) : ReadonlyDiskBuffer<1>(startingSectorNumber) { }

            class ShortFileName {
                public:
                    explicit ShortFileName(const uint8_t* sfnFieldPtr, uint8_t sfnFlags) : flags{sfnFlags} {
                        for(int i = 0; i < FULL_LENGTH; ++i) {
                            filename[i] = sfnFieldPtr[i];
                        }
                    }

                    auto c_str() const -> const char* {
                        return filename.data();
                    }

                    friend auto operator==(const ShortFileName& lhs, ShortFileName& rhs) -> bool {
                        return xstd::strcmp(lhs.filename.data(), rhs.filename.data()) == 0;
                    }
                    friend auto operator==(const ShortFileName& lhs, const char* rhs) -> bool {
                        return xstd::strcmp(lhs.filename.data(), rhs) == 0;
                    }
                    friend auto operator==(const char* lhs, const ShortFileName& rhs) -> bool {
                        return rhs == lhs;
                    }

                private:
                    static constexpr auto NAME_LENGTH = 8;
                    static constexpr auto EXTENSION_LENGTH = 3;
                    static constexpr auto FULL_LENGTH = NAME_LENGTH + EXTENSION_LENGTH;
                    xstd::array<char, FULL_LENGTH + 1> filename{};
                    uint8_t flags;
            };

            class DirectoryEntryHandle {
                public:
                    explicit DirectoryEntryHandle(const uint8_t* directoryEntryPtr) : entryPtr{directoryEntryPtr} { }
                
                    auto getShortFileName() const -> ShortFileName {
                        const auto sfnFlags = readFromMemoryAndPun<uint8_t>(entryPtr, 12);
                        return ShortFileName(entryPtr, sfnFlags);
                    }

                    auto getFileSizeInBytes() const -> uint32_t {
                        return readFromMemoryAndPun<uint32_t>(entryPtr, 28);
                    }

                    auto getFirstClusterNumber() const -> uint32_t {
                        const auto clusterNumberHighBits = readFromMemoryAndPun<uint16_t>(entryPtr, 20);
                        const auto clusterNumberLowBits = readFromMemoryAndPun<uint16_t>(entryPtr, 26);
                        return (clusterNumberHighBits << 16) + clusterNumberLowBits;
                    }

                    auto isReadOnly() const -> bool {
                        return entryPtr[11] & 0x01;
                    }

                    auto isHidden() const -> bool {
                        return entryPtr[11] & 0x02;
                    }

                    auto isSystemFile() const -> bool {
                        return entryPtr[11] & 0x04;
                    }

                    auto isVolumeID() const -> bool {
                        return entryPtr[11] & 0x08;
                    }

                    auto isDirectory() const -> bool {
                        return entryPtr[11] & 0x10;
                    }

                    auto isArchive() const -> bool {
                        return entryPtr[11] & 0x20;
                    }

                    auto isLongFileNameEntry() const -> bool {
                        return entryPtr[11] == 0x0F;
                    }
                
                private:
                    const uint8_t* entryPtr;
            };

            class DirectoryEntryIterator {
                public:
                    using difference_type = std::ptrdiff_t;
                    using value_type = DirectorySectorHandle;

                    explicit DirectoryEntryIterator(const uint8_t* directoryEntryPtr) : entryPtr{directoryEntryPtr} { }
                
                    auto operator*() const -> DirectoryEntryHandle {
                        return DirectoryEntryHandle(entryPtr);
                    }
                
                    auto operator++() -> DirectoryEntryIterator& {
                        entryPtr += ENTRY_SIZE;
                        return *this;
                    }
                
                    auto operator++(int) -> DirectoryEntryIterator {
                        auto tmp = *this;
                        ++*this;
                        return tmp;
                    }
                
                    auto operator--() -> DirectoryEntryIterator& {
                        entryPtr -= ENTRY_SIZE;
                        return *this;
                    }
                
                    auto operator--(int) -> DirectoryEntryIterator {
                        auto tmp = *this;
                        --*this;
                        return tmp;
                    }
                
                    friend auto operator==(const DirectoryEntryIterator& lhs, const DirectoryEntryIterator& rhs) -> bool {
                        return lhs.entryPtr == rhs.entryPtr;
                    }

                private:
                    static constexpr auto ENTRY_SIZE = 32;
                    const uint8_t* entryPtr; 
            };

            auto begin() const -> DirectoryEntryIterator {
                return DirectoryEntryIterator(bufferData());
            }

            auto end() const -> DirectoryEntryIterator {
                static constexpr auto SECTOR_SIZE = 512;
                return DirectoryEntryIterator(bufferData() + SECTOR_SIZE);
            }

    };

}
