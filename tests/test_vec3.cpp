#include <doctest/doctest.h>

#include "math/vec3.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Compile Time Tests                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(Vec3) == 3 * sizeof(float), "Vec3 must have no padding");
static_assert(std::is_trivially_copyable_v<Vec3>);

TEST_CASE("[] operator returns the correct element") {
    Vec3 v(27, 55, 82);
    float v_x = v[0];
    float v_y = v[1];
    float v_z = v[2];

    CHECK(v_x == 27.0);
    CHECK(v_y == 55.0);
    CHECK(v_z == 82.0);
}

TEST_CASE("Negation returns the negative of each element") {
    Vec3 v(27, 55, 82);
    Vec3 v_neg = -v;

    CHECK(v_neg[0] == -v[0]);
    CHECK(v_neg[1] == -v[1]);
    CHECK(v_neg[2] == -v[2]);
}

TEST_CASE("Operator += adds the 2 vectors") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(34, 2, 64);

    v1 += v2;

    CHECK(v1[0] == 61);
    CHECK(v1[1] == 57);
    CHECK(v1[2] == 146);
}

TEST_CASE("Operator + adds the 2 vectors and returns the sum") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(34, 2, 64);

    Vec3 v3 = v1 + v2;

    CHECK(v3[0] == 61);
    CHECK(v3[1] == 57);
    CHECK(v3[2] == 146);
}

TEST_CASE("Operator -= subtracts the 2 vectors") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(34, 2, 64);

    v1 -= v2;

    CHECK(v1[0] == -7);
    CHECK(v1[1] == 53);
    CHECK(v1[2] == 18);
}

TEST_CASE("Operator - subtracts the 2 vectors and returns the difference") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(34, 2, 64);

    Vec3 v3 = v1 - v2;

    CHECK(v3[0] == -7);
    CHECK(v3[1] == 53);
    CHECK(v3[2] == 18);
}

TEST_CASE("Operator *= multiplies the vector with the scalar") {
    Vec3 v1(27, 55, 82);

    v1 *= 2;

    CHECK(v1[0] == 54);
    CHECK(v1[1] == 110);
    CHECK(v1[2] == 164);
}

TEST_CASE("Operator * multiplies the vector with the scalar on the right") {
    Vec3 v1(27, 55, 82);

    Vec3 v2 = v1 * 2;

    CHECK(v2[0] == 54);
    CHECK(v2[1] == 110);
    CHECK(v2[2] == 164);
}

TEST_CASE("Operator * multiplies the vector with the scalar on the left") {
    Vec3 v1(27, 55, 82);

    Vec3 v2 = 2 * v1;

    CHECK(v2[0] == 54);
    CHECK(v2[1] == 110);
    CHECK(v2[2] == 164);
}

TEST_CASE("Operator /= divides the vector with the scalar") {
    Vec3 v1(27, 55, 82);

    v1 /= 2;

    CHECK(v1[0] == 13.5);
    CHECK(v1[1] == 27.5);
    CHECK(v1[2] == 41);
}

TEST_CASE("Operator / divides the vector with the scalar on the right") {
    Vec3 v1(27, 55, 82);

    Vec3 v2 = v1 / 2;

    CHECK(v2[0] == 13.5);
    CHECK(v2[1] == 27.5);
    CHECK(v2[2] == 41);
}

TEST_CASE("Operator *= multiplies the 2 vectors' components") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(2, 3, 10);

    v1 *= v2;

    CHECK(v1[0] == 54);
    CHECK(v1[1] == 165);
    CHECK(v1[2] == 820);
}

TEST_CASE("Operator * multiplies the 2 vectors' components and returns the product") {
    Vec3 v1(27, 55, 82);
    Vec3 v2(2, 3, 10);

    Vec3 v3 = v1 * v2;

    CHECK(v3[0] == 54);
    CHECK(v3[1] == 165);
    CHECK(v3[2] == 820);
}