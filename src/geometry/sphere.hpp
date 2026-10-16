#pragma once
#include <cmath>
#include <optional>

#include "hit_record.hpp"
#include "hittable.hpp"
#include "math/interval.hpp"
#include "math/ray.hpp"

namespace rt {

class Sphere : public rt::Hittable {
    rt::Point3 centre;
    float radius;

public:
    // ============================================================================================================================================ //
    //                                                                 Constructors                                                                 //
    // ============================================================================================================================================ //
    constexpr Sphere(const rt::Point3& c, float r) noexcept : centre(c), radius(r) {}

    // ============================================================================================================================================ //
    //                                                                 Hit Function                                                                 //
    // -------------------------------------------------------------------------------------------------------------------------------------------- //
    //                                    Ray: P(t) = O + t*D        Sphere: every point P with |P - C|^2 = r^2                                     //
    //                                          Substitute the ray into the sphere: |O + t*D - C|^2 = r^2                                           //
    //                                                Let oc = O - C, so (oc + t*D).(oc + t*D) = r^2                                                //
    //                                       Expand the dot product: (D.D)t^2 + 2(D.oc)t + (oc.oc - r^2) = 0                                        //
    //                 This is a quadratic in t: a = D.D, b = 2(D.oc), c = oc.oc - r^2 (D is not normalized, so a is not always 1)                  //
    // -------------------------------------------------------------------------------------------------------------------------------------------- //
    //                       discriminant = b^2 - 4ac: < 0 the ray misses, = 0 it grazes the surface, > 0 it enters and exits                       //
    //                           t = (-b -/+ sqrt(discriminant)) / 2a; a > 0, so t_near (minus root) <= t_far (plus root)                           //
    //                  t_near is used if it is in the interval, else t_far (ray starts inside the sphere, or t_near is behind it)                  //
    //                     outward_normal = (P - C) / r: points from the centre out through P, unit length because |P - C| = r                      //
    // ============================================================================================================================================ //
    [[nodiscard]] std::optional<rt::HitRecord> hit(const rt::Ray& ray, rt::Interval interval) const override {
        rt::Vec3 oc = ray.get_origin() - centre;
        float a = ray.get_direction().dot_product(ray.get_direction());
        float b = 2 * ray.get_direction().dot_product(oc);
        float c = oc.dot_product(oc) - (radius * radius);

        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return std::nullopt;
        }

        float t_near = (-b - std::sqrt(discriminant)) / (2 * a);
        float t_far = (-b + std::sqrt(discriminant)) / (2 * a);

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