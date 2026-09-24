#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace rt {

// Linear-space RGB film. Accumulate radiance here in floating point, then
// convert to 8-bit sRGB only when writing to disk.
class Image {
public:
    struct Pixel {
        float r = 0.0f, g = 0.0f, b = 0.0f;
    };

    Image(int width, int height);

    [[nodiscard]] int width() const noexcept { return width_; }
    [[nodiscard]] int height() const noexcept { return height_; }

    Pixel& at(int x, int y) { return pixels_[index(x, y)]; }
    [[nodiscard]] const Pixel& at(int x, int y) const { return pixels_[index(x, y)]; }

    // Clamps to [0,1], applies the sRGB transfer function, writes an 8-bit PNG.
    // Returns false on failure (e.g. the output directory doesn't exist).
    [[nodiscard]] bool write_png(const std::string& path) const;

private:
    [[nodiscard]] std::size_t index(int x, int y) const;

    int width_;
    int height_;
    std::vector<Pixel> pixels_;
};

// Exposed for unit testing.
[[nodiscard]] std::uint8_t linear_to_srgb8(float linear) noexcept;

}  // namespace rt
