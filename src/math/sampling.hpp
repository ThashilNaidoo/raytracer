#pragma once
#include <cmath>
#include <numbers>

#include "math/rng.hpp"
#include "math/vec3.hpp"

namespace rt {
[[nodiscard]] inline rt::Vec3 sample_uniform_sphere(rt::RNG& rng) {
    float u1 = rng.next_float();
    float u2 = rng.next_float();

    float z = 1 - 2 * u1;
    float r = std::sqrt(1 - z * z);
    float phi = 2 * std::numbers::pi_v<float> * u2;
    return rt::Vec3(r * std::cos(phi), r * std::sin(phi), z);
}
}  // namespace rt