#include <chrono>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>

#include "geometry/hittable_list.hpp"
#include "geometry/sphere.hpp"
#include "math/rng.hpp"
#include "render/camera.hpp"
#include "render/image.hpp"
#include "render/integrator.hpp"

int main(int argc, char** argv) {
    // ============================================================================================================================================ //
    //                                                                    Setup                                                                     //
    // ============================================================================================================================================ //
    const std::string out_path = argc > 1 ? argv[1] : "output/render.png";

    constexpr int width = 640;
    constexpr int height = 360;
    constexpr int samples_per_pixel = 1000;
    constexpr int path_trace_depth = 50;

    const auto start = std::chrono::steady_clock::now();

    rt::Image image(width, height);
    rt::Camera camera(width, height);

    // ============================================================================================================================================ //
    //                                                                    Scene                                                                     //
    // ============================================================================================================================================ //
    const rt::Point3 sphere_centre(0, 0, -1);

    const rt::Point3 floor_sphere_centre(0, -100.5, -1);

    rt::HittableList hittable_list;
    hittable_list.add_hittable(std::make_unique<rt::Sphere>(sphere_centre, 0.5f));
    hittable_list.add_hittable(std::make_unique<rt::Sphere>(floor_sphere_centre, 100.0f));

    // ============================================================================================================================================ //
    //                                                                 Render Loop                                                                  //
    // ============================================================================================================================================ //
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rt::Color pixel_color;
            rt::RNG rng(2814, static_cast<std::uint64_t>(y * width + x));

            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                float dx = rng.next_float() - 0.5f;
                float dy = rng.next_float() - 0.5f;
                rt::Ray curr_ray = camera.get_ray(static_cast<float>(x) + dx, static_cast<float>(y) + dy);

                pixel_color += rt::trace_path(curr_ray, hittable_list, path_trace_depth, rng);
            }

            pixel_color /= samples_per_pixel;
            image.at(x, y) = {pixel_color.get_x(), pixel_color.get_y(), pixel_color.get_z()};
        }
    }

    // ============================================================================================================================================ //
    //                                                                    Output                                                                    //
    // ============================================================================================================================================ //
    const auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start);

    const std::filesystem::path out(out_path);
    if (out.has_parent_path()) {
        std::filesystem::create_directories(out.parent_path());
    }
    if (!image.write_png(out_path)) {
        std::fprintf(stderr, "error: failed to write %s\n", out_path.c_str());
        return 1;
    }
    std::printf("wrote %s (%dx%d) in %.1f ms\n", out_path.c_str(), width, height, elapsed.count());
    return 0;
}
