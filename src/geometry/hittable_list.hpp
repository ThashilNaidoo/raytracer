#pragma once
#include <memory>
#include <vector>

#include "hittable.hpp"

namespace rt {
class HittableList : public rt::Hittable {
    std::vector<std::unique_ptr<rt::Hittable>> hittable_list;

public:
    void add_hittable(std::unique_ptr<rt::Hittable> new_hittable) { hittable_list.push_back(std::move(new_hittable)); }
    [[nodiscard]] std::optional<rt::HitRecord> hit(const rt::Ray& ray, rt::Interval interval) const override {
        std::optional<rt::HitRecord> closest_hit;
        for (const auto& hittable : hittable_list) {
            std::optional<rt::HitRecord> hit_record = hittable->hit(ray, interval);
            if (hit_record && hit_record->t < interval.max) {
                interval.max = hit_record->t;
                closest_hit = hit_record;
            }
        }

        return closest_hit;
    }
};
}  // namespace rt