#pragma once
#include "math/vec3.hpp"

namespace rt {
class Ray {
    Point3 origin;
    Vec3 direction;

public:
    // ========================================================================================== //
    //                                        Constructors                                        //
    // ------------------------------------------------------------------------------------------ //
    //         Direction is not normalized; Direction is not guaranteed to be unit length         //
    //                           t is the number of direction-lengths                             //
    //                       Will map to world distance if |direction| == 1                       //
    // ========================================================================================== //
    Ray() = default;
    constexpr Ray(const Point3& o, const Vec3& d) noexcept : origin(o), direction(d) {}

    // ========================================================================================== //
    //                                        Data Access                                         //
    // ========================================================================================== //
    [[nodiscard]] constexpr Point3 get_origin() const noexcept { return origin; }
    [[nodiscard]] constexpr Vec3 get_direction() const noexcept { return direction; }

    // ========================================================================================== //
    //                                        Point at t                                          //
    // ========================================================================================== //
    [[nodiscard]] constexpr Point3 at(float t) const noexcept { return origin + t * direction; }
};
}  // namespace rt