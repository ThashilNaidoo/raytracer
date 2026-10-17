#include "integrator.hpp"

#include <limits>

#include "math/sampling.hpp"

namespace rt {

rt::Color trace_path(const rt::Ray& ray, const rt::Hittable& hittable_list, int max_depth, rt::RNG& rng) {
    constexpr rt::Interval interval(1e-4f, std::numeric_limits<float>::infinity());
    constexpr float albedo = 0.5f;
    constexpr rt::Color color_bottom(1.0f, 1.0f, 1.0f);
    constexpr rt::Color color_top(1.0f, 0.5f, 0.2f);

    rt::Color throughput(1, 1, 1);
    rt::Ray curr_ray = ray;

    for (int i = 0; i < max_depth; ++i) {
        std::optional<rt::HitRecord> hit_record = hittable_list.hit(curr_ray, interval);

        if (!hit_record) {
            rt::Vec3 ray_normalized_direction = curr_ray.get_direction().unit_vector();
            float t = 0.5f * (ray_normalized_direction.get_y() + 1);
            return throughput * color_bottom.lerp(color_top, t);
        }

        throughput *= albedo;

        /* update curr ray */
        rt::Vec3 scatter_direction = rt::sample_uniform_sphere(rng);
        curr_ray = rt::Ray(hit_record->hit_point, scatter_direction + hit_record->outward_normal);
    }

    return rt::Color(0, 0, 0);
}
}  // namespace rt