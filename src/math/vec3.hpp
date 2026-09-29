#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>

namespace rt {
class Vec3 {
    float x;
    float y;
    float z;

public:
    // ========================================================================================== //
    //                                        Constructors                                        //
    // ========================================================================================== //

    Vec3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    // ========================================================================================== //
    //                                       Element Access                                       //
    // ========================================================================================== //
    float get_x() const { return x; }
    float get_y() const { return y; }
    float get_z() const { return z; }

    float& operator[](std::size_t index) {
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

    const float& operator[](std::size_t index) const {
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
    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3& operator+=(const Vec3& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }
    friend Vec3 operator+(Vec3 lhs, const Vec3& rhs);

    // ========================================================================================== //
    //                                        Subtraction                                         //
    // ========================================================================================== //
    Vec3& operator-=(const Vec3& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        this->z -= rhs.z;
        return *this;
    }
    friend Vec3 operator-(Vec3 lhs, const Vec3& rhs);

    // ========================================================================================== //
    //                                   Scalar Multiplication                                    //
    // ========================================================================================== //
    Vec3& operator*=(float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        return *this;
    }
    friend Vec3 operator*(Vec3 lhs, float scalar);
    friend Vec3 operator*(float scalar, Vec3 lhs);

    // ========================================================================================== //
    //                                      Scalar Division                                       //
    // ========================================================================================== //
    Vec3& operator/=(float scalar) {
        *this *= (1 / scalar);
        return *this;
    }
    friend Vec3 operator/(Vec3 lhs, float scalar);

    // ========================================================================================== //
    //                                 Component Multiplication                                   //
    // ========================================================================================== //
    Vec3& operator*=(const Vec3& rhs) {
        this->x *= rhs.x;
        this->y *= rhs.y;
        this->z *= rhs.z;
        return *this;
    }
    friend Vec3 operator*(Vec3 lhs, const Vec3& rhs);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                   Geometric Operations                                     //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // ========================================================================================== //
    //                                        Dot Product                                         //
    // ========================================================================================== //
    float dot_product(const Vec3& rhs) const {
        return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
    }

    // ========================================================================================== //
    //                                       Cross Product                                        //
    // ========================================================================================== //
    Vec3 cross_product(const Vec3& rhs) const {
        return Vec3((this->y * rhs.z) - (this->z * rhs.y), -((this->x * rhs.z) - (this->z * rhs.x)),
                    (this->x * rhs.y) - (this->y * rhs.x));
    }

    // ========================================================================================== //
    //                                      Squared Length                                        //
    // ========================================================================================== //
    float squared_length() const {
        return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
    }

    // ========================================================================================== //
    //                                          Length                                            //
    // ========================================================================================== //
    float length() const { return std::sqrt(this->squared_length()); }

    // ========================================================================================== //
    //                                        Unit Vector                                         //
    // ------------------------------------------------------------------------------------------ //
    //                      Returns the original vector when the length is 0                      //
    // ========================================================================================== //
    Vec3 unit_vector() const {
        float length = this->length();
        return length > 0 ? Vec3(this->x / length, this->y / length, this->z / length) : *this;
    }

    // ========================================================================================== //
    //                                        Reflection                                          //
    // ------------------------------------------------------------------------------------------ //
    //                               Normal should be a unit vector                               //
    // ========================================================================================== //
    Vec3 reflection(const Vec3& normal) const {
        return *this - 2 * (this->dot_product(normal)) * normal;
    }

    // ========================================================================================== //
    //                                        Refraction                                          //
    // ------------------------------------------------------------------------------------------ //
    //                     Incoming vector and normal should be unit vectors                      //
    //                        Normal must point against the incoming ray                          //
    //                     Returns the 0 vector on total internal reflection                      //
    // ========================================================================================== //
    Vec3 refraction(const Vec3& normal, float refractionIndexRatio) const {
        float c = -normal.dot_product(*this);
        float discriminant = 1 - (refractionIndexRatio * refractionIndexRatio) * (1 - c * c);

        if (discriminant < 0) {
            return Vec3(0, 0, 0);
        }

        return refractionIndexRatio * *this +
               (refractionIndexRatio * c - std::sqrt(discriminant)) * normal;
    }

    // ========================================================================================== //
    //                                  Component-Wise Minimum                                    //
    // ========================================================================================== //
    Vec3 component_wise_minimum(const Vec3& rhs) const {
        return Vec3(std::min(this->x, rhs.x), std::min(this->y, rhs.y), std::min(this->z, rhs.z));
    }

    // ========================================================================================== //
    //                                  Component-Wise Maximum                                    //
    // ========================================================================================== //
    Vec3 component_wise_maximum(const Vec3& rhs) const {
        return Vec3(std::max(this->x, rhs.x), std::max(this->y, rhs.y), std::max(this->z, rhs.z));
    }

    // ========================================================================================== //
    //                                   Linear Interpolation                                     //
    // ========================================================================================== //
    Vec3 lerp(const Vec3& b, float t) const { return *this + t * (b - *this); }
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 Friend Function Implementation                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////
inline Vec3 operator+(Vec3 lhs, const Vec3& rhs) {
    lhs += rhs;
    return lhs;
}

inline Vec3 operator-(Vec3 lhs, const Vec3& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Vec3 operator*(Vec3 lhs, float scalar) {
    lhs *= scalar;
    return lhs;
}

inline Vec3 operator*(float scalar, Vec3 lhs) {
    lhs *= scalar;
    return lhs;
}

inline Vec3 operator/(Vec3 lhs, float scalar) {
    lhs /= scalar;
    return lhs;
}

inline Vec3 operator*(Vec3 lhs, const Vec3& rhs) {
    lhs *= rhs;
    return lhs;
}

using Color = Vec3;
using Point3 = Vec3;
}  // namespace rt
