// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <algorithm>
#include <array>

#include "common/common_types.h"
#include "video_core/vulkan_common/vulkan.h"

namespace Vulkan {

inline bool BuildsUnoptimized(VkDriverId driver_id, u64 shader_hash) {
    // The Legend of Zelda: Ocarina of Time (0400486024DEC000), driver 2.0.353 on an RX 6600 XT
    static constexpr std::array<u64, 2> amd_proprietary{
        0xeff3ccbe1438679dULL, // compute shader built as the AV1 intro starts: 6 min (#200)
        0xf9ea14a22394f5b1ULL, // compute shader built as the AV1 intro starts: 18 min (#200)
    };
    return driver_id == VK_DRIVER_ID_AMD_PROPRIETARY &&
           std::ranges::find(amd_proprietary, shader_hash) != amd_proprietary.end();
}

/// Graphics stages whose pipelines took 12 to 17 s inside AMD's optimizer in one Ocarina of Time
/// session (RX 6650 XT, driver 2.0.353). Any pipeline that contains one is built unoptimized.
inline bool BuildsGraphicsUnoptimized(VkDriverId driver_id, u64 stage_hash) {
    static constexpr std::array<u64, 6> amd_proprietary{
        0xf16638b51d8e93acULL, 0x2a36b86df54c3078ULL, 0x22f53780925c9fdcULL,
        0x91f539a6c54c97dbULL, 0x41a89b6df7ab4188ULL, 0xc4a9495a97b2ae03ULL,
    };
    return driver_id == VK_DRIVER_ID_AMD_PROPRIETARY &&
           std::ranges::find(amd_proprietary, stage_hash) != amd_proprietary.end();
}

} // namespace Vulkan
