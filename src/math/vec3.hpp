#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <ostream>

namespace rt {
class Vec3 {
    float x;
    float y;
    float z;

public:
    // ========================================================================================== //
    //                                        Constructors                                        //
    // ========================================================================================== //

    constexpr Vec3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}

    constexpr Vec3(float x_, float y_, float z_) noexcept : x(x_), y(y_), z(z_) {}

    // ========================================================================================== //
    //                                       Element Access                                       //
    // ========================================================================================== //
    [[nodiscard]] constexpr float get_x() const noexcept { return x; }
    [[nodiscard]] constexpr float get_y() const noexcept { return y; }
    [[nodiscard]] constexpr float get_z() const noexcept { return z; }

    [[nodiscard]] constexpr float& operator[](std::size_t index) noexcept {
        assert(index < 3);
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
        }
    }

    [[nodiscard]] constexpr const float& operator[](std::size_t index) const noexcept {
        assert(index < 3);
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                   Arithmetic Operations                                    //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // ========================================================================================== //
    //                                          Addition                                          //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 operator-() const noexcept { return Vec3(-x, -y, -z); }

    constexpr Vec3& operator+=(const Vec3& rhs) noexcept {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }
    friend constexpr Vec3 operator+(Vec3 lhs, const Vec3& rhs) noexcept;

    // ========================================================================================== //
    //                                        Subtraction                                         //
    // ========================================================================================== //
    constexpr Vec3& operator-=(const Vec3& rhs) noexcept {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }
    friend constexpr Vec3 operator-(Vec3 lhs, const Vec3& rhs) noexcept;

    // ========================================================================================== //
    //                                   Scalar Multiplication                                    //
    // ========================================================================================== //
    constexpr Vec3& operator*=(float scalar) noexcept {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    friend constexpr Vec3 operator*(Vec3 lhs, float scalar) noexcept;
    friend constexpr Vec3 operator*(float scalar, Vec3 lhs) noexcept;

    // ========================================================================================== //
    //                                      Scalar Division                                       //
    // ------------------------------------------------------------------------------------------ //
    //                        The caller should check that scalar is not 0                        //
    // ========================================================================================== //
    constexpr Vec3& operator/=(float scalar) noexcept {
        assert(scalar != 0.0f);

        *this *= (1 / scalar);
        return *this;
    }
    friend constexpr Vec3 operator/(Vec3 lhs, float scalar) noexcept;

    // ========================================================================================== //
    //                                 Component Multiplication                                   //
    // ========================================================================================== //
    constexpr Vec3& operator*=(const Vec3& rhs) noexcept {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }
    friend constexpr Vec3 operator*(Vec3 lhs, const Vec3& rhs) noexcept;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                   Geometric Operations                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // ========================================================================================== //
    //                                        Dot Product                                         //
    // ========================================================================================== //
    [[nodiscard]] constexpr float dot_product(const Vec3& rhs) const noexcept {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }

    // ========================================================================================== //
    //                                       Cross Product                                        //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 cross_product(const Vec3& rhs) const noexcept {
        return Vec3((this->y * rhs.z) - (this->z * rhs.y), -((this->x * rhs.z) - (this->z * rhs.x)),
                    (this->x * rhs.y) - (this->y * rhs.x));
    }

    // ========================================================================================== //
    //                                      Squared Length                                        //
    // ========================================================================================== //
    [[nodiscard]] constexpr float squared_length() const noexcept {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    // ========================================================================================== //
    //                                          Length                                            //
    // ========================================================================================== //
    [[nodiscard]] float length() const noexcept { return std::sqrt(this->squared_length()); }

    // ========================================================================================== //
    //                                        Unit Vector                                         //
    // ------------------------------------------------------------------------------------------ //
    //                      Returns the original vector when the length is 0                      //
    // ========================================================================================== //
    [[nodiscard]] Vec3 unit_vector() const noexcept {
        float length = this->length();
        return length > 0 ? Vec3(this->x / length, this->y / length, this->z / length) : *this;
    }

    // ========================================================================================== //
    //                                        Reflection                                          //
    // ------------------------------------------------------------------------------------------ //
    //                               Normal should be a unit vector                               //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 reflection(const Vec3& normal) const noexcept {
        return *this - 2 * (this->dot_product(normal)) * normal;
    }

    // ========================================================================================== //
    //                                        Refraction                                          //
    // ------------------------------------------------------------------------------------------ //
    //                     Incoming vector and normal should be unit vectors                      //
    //                        Normal must point against the incoming ray                          //
    //                     Returns the 0 vector on total internal reflection                      //
    // ========================================================================================== //
    [[nodiscard]] Vec3 refraction(const Vec3& normal, float refraction_index_ratio) const noexcept {
        float c = -normal.dot_product(*this);
        float discriminant = 1 - (refraction_index_ratio * refraction_index_ratio) * (1 - c * c);

        if (discriminant < 0) {
            return Vec3(0, 0, 0);
        }

        return refraction_index_ratio * *this +
               (refraction_index_ratio * c - std::sqrt(discriminant)) * normal;
    }

    // ========================================================================================== //
    //                                  Component-Wise Minimum                                    //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 component_wise_minimum(const Vec3& rhs) const noexcept {
        return Vec3(std::min(this->x, rhs.x), std::min(this->y, rhs.y), std::min(this->z, rhs.z));
    }

    // ========================================================================================== //
    //                                  Component-Wise Maximum                                    //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 component_wise_maximum(const Vec3& rhs) const noexcept {
        return Vec3(std::max(this->x, rhs.x), std::max(this->y, rhs.y), std::max(this->z, rhs.z));
    }

    // ========================================================================================== //
    //                                   Linear Interpolation                                     //
    // ========================================================================================== //
    [[nodiscard]] constexpr Vec3 lerp(const Vec3& b, float t) const noexcept {
        return *this + t * (b - *this);
    }

    // ========================================================================================== //
    //                                     Near Zero Check                                        //
    // ========================================================================================== //
    [[nodiscard]] bool is_near_zero(float epsilon = 1e-7f) const noexcept {
        return (std::abs((*this)[0]) <= epsilon) && (std::abs((*this)[1]) <= epsilon) &&
               (std::abs((*this)[2]) <= epsilon);
    }

    // ========================================================================================== //
    //                                    Largest Component                                       //
    // ========================================================================================== //
    [[nodiscard]] constexpr std::size_t largest_component() const noexcept {
        if ((*this)[0] > (*this)[1]) {
            if ((*this)[0] > (*this)[2]) {
                return 0;
            } else {
                return 2;
            }
        } else if ((*this)[1] > (*this)[2]) {
            return 1;
        } else {
            return 2;
        }
    }

    // ========================================================================================== //
    //                                      Stream Output                                         //
    // ========================================================================================== //
    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

    // ========================================================================================== //
    //                                  Approximate Equality                                      //
    // ========================================================================================== //
    [[nodiscard]] bool approximate_equality(const Vec3& rhs, float epsilon = 1e-7f) const noexcept {
        return (std::abs((*this)[0] - rhs[0]) <= epsilon) &&
               (std::abs((*this)[1] - rhs[1]) <= epsilon) &&
               (std::abs((*this)[2] - rhs[2]) <= epsilon);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 Friend Function Implementation                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////
[[nodiscard]] inline constexpr Vec3 operator+(Vec3 lhs, const Vec3& rhs) noexcept {
    lhs += rhs;
    return lhs;
}

[[nodiscard]] inline constexpr Vec3 operator-(Vec3 lhs, const Vec3& rhs) noexcept {
    lhs -= rhs;
    return lhs;
}

[[nodiscard]] inline constexpr Vec3 operator*(Vec3 lhs, float scalar) noexcept {
    lhs *= scalar;
    return lhs;
}

[[nodiscard]] inline constexpr Vec3 operator*(float scalar, Vec3 lhs) noexcept {
    lhs *= scalar;
    return lhs;
}

[[nodiscard]] inline constexpr Vec3 operator/(Vec3 lhs, float scalar) noexcept {
    lhs /= scalar;
    return lhs;
}

[[nodiscard]] inline constexpr Vec3 operator*(Vec3 lhs, const Vec3& rhs) noexcept {
    lhs *= rhs;
    return lhs;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
    return os;
}

using Color = Vec3;
using Point3 = Vec3;
}  // namespace rt
