#include <type_traits>

#include <doctest/doctest.h>

#include "math/ray.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Compile Time Tests                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(rt::Ray) == 2 * sizeof(rt::Vec3), "Ray must have no padding");
static_assert(std::is_trivially_copyable_v<rt::Ray>);
constexpr rt::Ray cr(rt::Point3(0, 0, 0), rt::Vec3(1, 1, 0));
static_assert(cr.at(2).get_x() == 2);

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           Unit Tests                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("get_origin returns the correct vector") {
    rt::Ray r(rt::Vec3(34, 47, 0), rt::Vec3(1, 2, 0));

    CHECK(r.get_origin()[0] == 34);
    CHECK(r.get_origin()[1] == 47);
    CHECK(r.get_origin()[2] == 0);
}

TEST_CASE("get_direction returns the correct vector") {
    rt::Ray r(rt::Vec3(34, 47, 0), rt::Vec3(1, 2, 0));

    CHECK(r.get_direction()[0] == 1);
    CHECK(r.get_direction()[1] == 2);
    CHECK(r.get_direction()[2] == 0);
}

TEST_CASE("at calculates and returns the correct point") {
    rt::Ray r(rt::Vec3(34, 47, 0), rt::Vec3(1, 2, 0));
    rt::Point3 p = r.at(5);

    CHECK(p[0] == 39);
    CHECK(p[1] == 57);
    CHECK(p[2] == 0);
}

TEST_CASE("at calculates and returns the correct point with the correct distance moved") {
    rt::Point3 origin(34, 47, 0);
    rt::Vec3 direction(1, 2, 0);
    rt::Ray r(origin, direction);
    float t = 0.5f;
    rt::Point3 p = r.at(t);

    float distance_moved = (p - origin).length();
    float expected_distance_moved = t * direction.length();

    CHECK(distance_moved == doctest::Approx(expected_distance_moved));
}
