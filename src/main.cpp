#include <chrono>
#include <cstdio>
#include <filesystem>
#include <string>

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
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // TODO(week 1): generate a camera ray for (x, y) and trace it.
            // Sky-style blend: white at the bottom, light blue at the top.
            const float t = 1.0f - static_cast<float>(y) / static_cast<float>(height - 1);
            image.at(x, y) = {(1.0f - t) + t * 0.5f, (1.0f - t) + t * 0.7f, 1.0f};
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
