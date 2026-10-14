#pragma once

#include "math/vec3.hpp"
namespace rt {

struct HitRecord {
    float t;
    rt::Point3 hit_point;
    rt::Vec3 outward_normal;
};
}  // namespace rt