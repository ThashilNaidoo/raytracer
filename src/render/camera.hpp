#pragma once
#include "math/ray.hpp"
#include "math/vec3.hpp"

namespace rt {
class Camera {
    Point3 eye_position_;
    Point3 first_pixel_centre_;
    Vec3 horizontal_pixel_step_;
    Vec3 vertical_pixel_step_;

public:
    // ========================================================================================== //
    //                                        Constructors                                        //
    // ========================================================================================== //
    Camera(int width, int height);

    // ========================================================================================== //
    //                                        Ray Function                                        //
    // ========================================================================================== //
    constexpr Ray get_ray(int i, int j) const {
        Point3 destination = first_pixel_centre_ + static_cast<float>(i) * horizontal_pixel_step_ +
                             static_cast<float>(j) * vertical_pixel_step_;

        Vec3 direction = destination - eye_position_;

        return Ray(eye_position_, direction);
    }
};
}  // namespace rt