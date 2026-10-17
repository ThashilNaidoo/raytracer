#pragma once

#include "geometry/hittable.hpp"
#include "math/ray.hpp"
#include "math/rng.hpp"
#include "math/vec3.hpp"

namespace rt {
rt::Color trace_path(const rt::Ray& ray, const rt::Hittable& hittable_list, int max_depth, rt::RNG& rng);
}