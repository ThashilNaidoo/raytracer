#include <cmath>
#include <type_traits>

#include <doctest/doctest.h>

#include "math/vec3.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Compile Time Tests                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(rt::Vec3) == 3 * sizeof(float), "Vec3 must have no padding");
static_assert(std::is_trivially_copyable_v<rt::Vec3>);
static_assert(rt::Vec3(1, 2, 0).get_x() == 1);
static_assert(rt::Vec3(1, 2, 0).get_y() == 2);
static_assert(rt::Vec3(1, 2, 0).get_z() == 0);
static_assert(rt::Vec3().get_x() == 0);
static_assert(rt::Vec3().get_y() == 0);
static_assert(rt::Vec3().get_z() == 0);
static_assert(rt::Vec3(1, 2, 0)[0] == 1);
static_assert(rt::Vec3(1, 2, 0)[1] == 2);
static_assert(rt::Vec3(1, 2, 0)[2] == 0);
static_assert([]() {
    rt::Vec3 v(1, 2, 3);
    v[1] = 4;
    return v.get_x() == 1 && v.get_y() == 4 && v.get_z() == 3;
}());

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           Unit Tests                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("[] operator returns the correct element") {
    rt::Vec3 v(27, 55, 82);
    float v_x = v[0];
    float v_y = v[1];
    float v_z = v[2];

    CHECK(v_x == 27.0);
    CHECK(v_y == 55.0);
    CHECK(v_z == 82.0);
}

TEST_CASE("[] non-const operator returns the correct element and allows updates") {
    rt::Vec3 v(27, 55, 82);
    v[0] = 34;
    float v_x = v[0];
    float v_y = v[1];
    float v_z = v[2];

    CHECK(v_x == 34.0);
    CHECK(v_y == 55.0);
    CHECK(v_z == 82.0);
}

TEST_CASE("Negation returns the negative of each element") {
    rt::Vec3 v(27, 55, 82);
    rt::Vec3 v_neg = -v;

    CHECK(v_neg[0] == -v[0]);
    CHECK(v_neg[1] == -v[1]);
    CHECK(v_neg[2] == -v[2]);
}

TEST_CASE("Operator += adds the 2 vectors") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(34, 2, 64);

    v1 += v2;

    CHECK(v1[0] == 61);
    CHECK(v1[1] == 57);
    CHECK(v1[2] == 146);
}

TEST_CASE("Operator + adds the 2 vectors and returns the sum") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(34, 2, 64);

    rt::Vec3 v3 = v1 + v2;

    CHECK(v3[0] == 61);
    CHECK(v3[1] == 57);
    CHECK(v3[2] == 146);
}

TEST_CASE("Operator -= subtracts the 2 vectors") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(34, 2, 64);

    v1 -= v2;

    CHECK(v1[0] == -7);
    CHECK(v1[1] == 53);
    CHECK(v1[2] == 18);
}

TEST_CASE("Operator - subtracts the 2 vectors and returns the difference") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(34, 2, 64);

    rt::Vec3 v3 = v1 - v2;

    CHECK(v3[0] == -7);
    CHECK(v3[1] == 53);
    CHECK(v3[2] == 18);
}

TEST_CASE("Operator *= multiplies the vector with the scalar") {
    rt::Vec3 v1(27, 55, 82);

    v1 *= 2;

    CHECK(v1[0] == 54);
    CHECK(v1[1] == 110);
    CHECK(v1[2] == 164);
}

TEST_CASE("Operator * multiplies the vector with the scalar on the right") {
    rt::Vec3 v1(27, 55, 82);

    rt::Vec3 v2 = v1 * 2;

    CHECK(v2[0] == 54);
    CHECK(v2[1] == 110);
    CHECK(v2[2] == 164);
}

TEST_CASE("Operator * multiplies the vector with the scalar on the left") {
    rt::Vec3 v1(27, 55, 82);

    rt::Vec3 v2 = 2 * v1;

    CHECK(v2[0] == 54);
    CHECK(v2[1] == 110);
    CHECK(v2[2] == 164);
}

TEST_CASE("Operator /= divides the vector with the scalar") {
    rt::Vec3 v1(27, 55, 82);

    v1 /= 2;

    CHECK(v1[0] == 13.5);
    CHECK(v1[1] == 27.5);
    CHECK(v1[2] == 41);
}

TEST_CASE("Operator / divides the vector with the scalar on the right") {
    rt::Vec3 v1(27, 55, 82);

    rt::Vec3 v2 = v1 / 2;

    CHECK(v2[0] == 13.5);
    CHECK(v2[1] == 27.5);
    CHECK(v2[2] == 41);
}

TEST_CASE("Operator *= multiplies the 2 vectors' components") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(2, 3, 10);

    v1 *= v2;

    CHECK(v1[0] == 54);
    CHECK(v1[1] == 165);
    CHECK(v1[2] == 820);
}

TEST_CASE("Operator * multiplies the 2 vectors' components and returns the product") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(2, 3, 10);

    rt::Vec3 v3 = v1 * v2;

    CHECK(v3[0] == 54);
    CHECK(v3[1] == 165);
    CHECK(v3[2] == 820);
}

TEST_CASE("Dot product returns the correct value") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(2, 3, 10);
    float dot_product_value = v1.dot_product(v2);

    CHECK(dot_product_value == 1039);
}

TEST_CASE("Cross product returns the correct vector") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 v2(2, 3, 10);
    rt::Vec3 v3 = v1.cross_product(v2);

    CHECK(v3[0] == 304);
    CHECK(v3[1] == -106);
    CHECK(v3[2] == -29);
}

TEST_CASE("Squared length returns the correct value") {
    rt::Vec3 v1(27, 55, 82);
    float squared_length = v1.squared_length();

    CHECK(squared_length == 10478);
}

TEST_CASE("Length returns the correct value") {
    rt::Vec3 v1(27, 55, 82);
    float length = v1.length();

    CHECK(length == doctest::Approx(sqrtf(10478)));
}

TEST_CASE("Unit vector returns the correct vector") {
    rt::Vec3 v1(27, 55, 82);
    rt::Vec3 unit_vector = v1.unit_vector();

    float length = sqrtf((27 * 27) + (55 * 55) + (82 * 82));

    CHECK(unit_vector[0] == doctest::Approx(27 / length));
    CHECK(unit_vector[1] == doctest::Approx(55 / length));
    CHECK(unit_vector[2] == doctest::Approx(82 / length));
    CHECK(unit_vector.length() == doctest::Approx(1.0));
}

TEST_CASE("Reflection returns the correct ray") {
    rt::Vec3 ray(-0.5, -0.5, 0);

    rt::Vec3 reflected_ray = ray.reflection(rt::Vec3(0, 1, 0));

    CHECK(reflected_ray[0] == -0.5);
    CHECK(reflected_ray[1] == 0.5);
    CHECK(reflected_ray[2] == 0);
    CHECK(reflected_ray.length() == doctest::Approx(ray.length()));
}

TEST_CASE("Refraction returns the correct ray") {
    rt::Vec3 incoming_ray(1, -1, 0);
    rt::Vec3 normal(0, 1, 0);
    incoming_ray = incoming_ray.unit_vector();
    float ratio = 1.0f / 1.5f;

    float theta_i = acosf(std::abs(incoming_ray.dot_product(normal)));
    float theta_t = asinf(ratio * sinf(theta_i));

    rt::Vec3 refracted_ray = incoming_ray.refraction(normal, ratio);

    CHECK(refracted_ray[0] == doctest::Approx(sinf(theta_t)));
    CHECK(refracted_ray[1] == doctest::Approx(-cosf(theta_t)));
    CHECK(refracted_ray[2] == doctest::Approx(0));
}

TEST_CASE("Total internal reflection returns the zero vector") {
    rt::Vec3 incoming_ray(1, -0.3f, 0);
    rt::Vec3 normal(0, 1, 0);
    float ratio = 1.5;

    incoming_ray = incoming_ray.unit_vector();
    rt::Vec3 refracted_ray = incoming_ray.refraction(normal, ratio);

    CHECK(refracted_ray[0] == 0);
    CHECK(refracted_ray[1] == 0);
    CHECK(refracted_ray[2] == 0);
}

TEST_CASE("Component wise minimum returns the correct vector") {
    rt::Vec3 v1(2, 55, 82);
    rt::Vec3 v2(27, 3, 10);

    rt::Vec3 min = v1.component_wise_minimum(v2);

    CHECK(min[0] == 2);
    CHECK(min[1] == 3);
    CHECK(min[2] == 10);
}

TEST_CASE("Component wise maximum returns the correct vector") {
    rt::Vec3 v1(2, 55, 82);
    rt::Vec3 v2(27, 3, 10);

    rt::Vec3 max = v1.component_wise_maximum(v2);

    CHECK(max[0] == 27);
    CHECK(max[1] == 55);
    CHECK(max[2] == 82);
}

TEST_CASE("Near zero check returns true when a component is close to 0") {
    rt::Vec3 v1(0.000000000000000001f, 0, -0.00000000000000001f);

    CHECK(v1.is_near_zero() == true);
}

TEST_CASE("Largest component returns the correct index") {
    rt::Vec3 v1(2, 55, 82);

    CHECK(v1.largest_component() == 2);
}

TEST_CASE("Approximate equality returns true for 2 vectors that are similar and false otherwise") {
    rt::Vec3 v1(2, 55, 82);
    rt::Vec3 v2(2, 55, 82);
    rt::Vec3 v3(1, 55, 82);

    CHECK(v1.approximate_equality(v2) == true);
    CHECK(v1.approximate_equality(v3) == false);
}