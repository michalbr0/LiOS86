#pragma once

#include <stdint.h>

#include "xstd/expected.hpp"
#include "xstd/array.hpp"

namespace LiOS86 {

    // uses PIO to read sectors from the primary master ATA disk (LBA24 addressing)
    auto readSectors(uint32_t logicalBlockAddress, uint8_t numberOfSectors) -> xstd::expected<xstd::array<uint8_t, 512>, int>;

}
