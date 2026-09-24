#include <cmath>
#include <limits>

#include <doctest/doctest.h>

#include "render/image.hpp"

TEST_CASE("linear_to_srgb8 clamps and handles edge cases") {
    CHECK(rt::linear_to_srgb8(0.0f) == 0);
    CHECK(rt::linear_to_srgb8(1.0f) == 255);
    CHECK(rt::linear_to_srgb8(-1.0f) == 0);
    CHECK(rt::linear_to_srgb8(10.0f) == 255);
    CHECK(rt::linear_to_srgb8(std::numeric_limits<float>::quiet_NaN()) == 0);
    CHECK(rt::linear_to_srgb8(std::numeric_limits<float>::infinity()) == 255);
}

TEST_CASE("linear_to_srgb8 applies the sRGB curve, not plain gamma") {
    // Linear 0.5 is ~188 in sRGB. If you see 128, gamma correction is missing.
    CHECK(rt::linear_to_srgb8(0.5f) == 188);
    // Linear 0.214 is roughly sRGB mid-grey.
    CHECK(rt::linear_to_srgb8(0.214f) == doctest::Approx(128).epsilon(0.01));
}

TEST_CASE("Image stores pixels by (x, y)") {
    rt::Image img(4, 3);
    CHECK(img.width() == 4);
    CHECK(img.height() == 3);
    img.at(3, 2) = {1.0f, 0.5f, 0.25f};
    CHECK(img.at(3, 2).g == doctest::Approx(0.5f));
    CHECK(img.at(0, 0).r == doctest::Approx(0.0f));
}

TEST_CASE("Image rejects invalid dimensions") {
    CHECK_THROWS(rt::Image(0, 10));
    CHECK_THROWS(rt::Image(10, -1));
}
