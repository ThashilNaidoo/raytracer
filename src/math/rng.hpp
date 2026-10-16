#pragma once
#include <cstdint>

namespace rt {
class RNG {
    std::uint64_t state;
    std::uint64_t inc;

public:
    constexpr RNG(std::uint64_t seed, std::uint64_t sequence) noexcept : state(0), inc((sequence << 1) | 1) {
        next_u32();
        state += seed;
        next_u32();
    }

    constexpr std::uint32_t next_u32() noexcept {
        std::uint64_t old_state = state;
        state = old_state * 6364136223846793005ULL + inc;
        std::uint32_t xorshifted = static_cast<std::uint32_t>(((old_state >> 18) ^ old_state) >> 27);
        std::uint32_t rot = static_cast<std::uint32_t>(old_state >> 59);
        return (xorshifted >> rot) | (xorshifted << ((32 - rot) & 31));
    }

    constexpr float next_float() noexcept {
        std::uint32_t next_int = next_u32();
        return static_cast<float>(next_int >> 8) * 0x1p-24f;
    }
};
}  // namespace rt