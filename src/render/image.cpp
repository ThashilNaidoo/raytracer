#include "render/image.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>

// Exactly one translation unit in the project defines the stb implementation.
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace rt {

Image::Image(int width, int height) : width_(width), height_(height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Image dimensions must be positive");
    }
    pixels_.resize(static_cast<std::size_t>(width) * static_cast<std::size_t>(height));
}

std::size_t Image::index(int x, int y) const {
    assert(x >= 0 && x < width_ && y >= 0 && y < height_);
    return static_cast<std::size_t>(y) * static_cast<std::size_t>(width_) +
           static_cast<std::size_t>(x);
}

std::uint8_t linear_to_srgb8(float linear) noexcept {
    // NaN fails every comparison, so treat it as black rather than letting it
    // propagate into undefined float->int conversion.
    if (!(linear > 0.0f)) return 0;
    if (linear >= 1.0f) return 255;
    const float srgb =
        linear <= 0.0031308f ? 12.92f * linear : 1.055f * std::pow(linear, 1.0f / 2.4f) - 0.055f;
    return static_cast<std::uint8_t>(std::lround(srgb * 255.0f));
}

bool Image::write_png(const std::string& path) const {
    std::vector<std::uint8_t> bytes;
    bytes.reserve(pixels_.size() * 3);
    for (const Pixel& p : pixels_) {
        bytes.push_back(linear_to_srgb8(p.r));
        bytes.push_back(linear_to_srgb8(p.g));
        bytes.push_back(linear_to_srgb8(p.b));
    }
    const int stride = width_ * 3;
    return stbi_write_png(path.c_str(), width_, height_, 3, bytes.data(), stride) != 0;
}

}  // namespace rt
