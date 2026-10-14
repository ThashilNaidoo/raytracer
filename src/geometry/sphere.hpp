#pragma once
#include <cmath>
#include <optional>

#include "hit_record.hpp"
#include "math/interval.hpp"
#include "math/ray.hpp"

namespace rt {

class Sphere {
    rt::Point3 centre;
    float radius;

public:
    Sphere(rt::Point3 c, float r) : centre(c), radius(r) {}

    [[nodiscard]] std::optional<rt::HitRecord> hit(const rt::Ray& ray,
                                                   rt::Interval interval) const {
        rt::Vec3 oc = ray.get_origin() - centre;
        float a = ray.get_direction().dot_product(ray.get_direction());
        float b = 2 * ray.get_direction().dot_product(oc);
        float c = oc.dot_product(oc) - (radius * radius);

        float det = b * b - 4 * a * c;

        if (det < 0) {
            return std::nullopt;
        }

        float t_near = (-b - std::sqrt(det)) / (2 * a);
        float t_far = (-b + std::sqrt(det)) / (2 * a);

        float t;

        if (interval.contains(t_near)) {
            t = t_near;
        } else if (interval.contains(t_far)) {
            t = t_far;
        } else {
            return std::nullopt;
        }

        rt::Point3 hit_point = ray.at(t);
        rt::Vec3 outward_normal = (hit_point - centre) / radius;

        return rt::HitRecord{.t = t, .hit_point = hit_point, .outward_normal = outward_normal};
    }
};
}  // namespace rt