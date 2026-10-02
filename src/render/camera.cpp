#include "render/camera.hpp"

rt::Camera::Camera(int width, int height) {
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    float viewport_width = aspect_ratio * viewport_height;

    eye_position_ = rt::Point3();
    rt::Vec3 vertical_edge_vector(0, -viewport_height, 0);
    rt::Vec3 horizontal_edge_vector(viewport_width, 0, 0);

    vertical_pixel_step_ = vertical_edge_vector / static_cast<float>(height);
    horizontal_pixel_step_ = horizontal_edge_vector / static_cast<float>(width);

    rt::Point3 viewport_top_left = eye_position_ - rt::Vec3(0, 0, focal_length) -
                                   0.5f * vertical_edge_vector - 0.5f * horizontal_edge_vector;

    first_pixel_centre_ =
        viewport_top_left + 0.5f * vertical_pixel_step_ + 0.5f * horizontal_pixel_step_;
}