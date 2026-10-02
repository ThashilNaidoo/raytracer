#include <chrono>
#include <cstdio>
#include <filesystem>
#include <string>

#include "render/camera.hpp"
#include "render/image.hpp"

// Pipeline smoke test: renders a gradient so you can confirm the build, PNG
// output and sRGB conversion all work before any ray tracing exists.
// Week 1 replaces the body of the pixel loop with camera rays + ray_color().
int main(int argc, char** argv) {
    const std::string out_path = argc > 1 ? argv[1] : "output/render.png";

    constexpr int width = 640;
    constexpr int height = 360;

    const auto start = std::chrono::steady_clock::now();

    rt::Image image(width, height);
    rt::Camera camera(width, height);
    const rt::Color color_bottom(1.0f, 1.0f, 1.0f);
    const rt::Color color_top(1.0f, 0.5f, 0.2f);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rt::Ray curr_ray = camera.get_ray(x, y);
            rt::Vec3 ray_normalized_direction = curr_ray.get_direction().unit_vector();

            float t = 0.5f * (ray_normalized_direction.get_y() + 1);
            rt::Color pixel_color = color_bottom.lerp(color_top, t);

            image.at(x, y) = {pixel_color.get_x(), pixel_color.get_y(), pixel_color.get_z()};
        }
    }

    const auto elapsed =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start);

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
