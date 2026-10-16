#pragma once
#include <optional>

#include "hit_record.hpp"
#include "math/interval.hpp"
#include "math/ray.hpp"

namespace rt {
class Hittable {
public:
    [[nodiscard]] virtual std::optional<rt::HitRecord> hit(const rt::Ray& ray, rt::Interval interval) const = 0;
    virtual ~Hittable() = default;
};
}  // namespace rt