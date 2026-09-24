#pragma once

#include <stdexcept>

class Vec3 {
public:
    // Constructors
    Vec3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    };

    Vec3(float x, float y, float z) : x(x), y(y), z(z) {};

    Vec3(const Vec3& source) {
        this->x = source.x;
        this->y = source.y;
        this->z = source.z;
    };

    // Element Access
    float getX() { return x; };
    float getY() { return y; };
    float getZ() { return z; };

    float& operator[](std::size_t index) {
        float elementArray[] = {x, y, z};

        if (index < 0 or index > 2) {
            throw std::out_of_range("Index out of bounds.");
        }
        return elementArray[index];
    };

    const float& operator[](std::size_t index) const {
        float elementArray[] = {x, y, z};

        if (index < 0 or index > 2) {
            throw std::out_of_range("Index out of bounds.");
        }
        return elementArray[index];
    };

private:
    float x;
    float y;
    float z;
};