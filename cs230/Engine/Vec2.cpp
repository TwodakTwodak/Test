#include "Vec2.h"

bool Math::vec3::operator==(const vec3& v) {
    return (x == v.x && y == v.y && z == v.z);
}

bool Math::vec3::operator!=(const vec3& v) {
    return (x != v.x || y != v.y || z != v.z);
}

Math::vec3 Math::vec3::operator+(const vec3& v) {
    return { x + v.x, y + v.y, z + v.z };
}

Math::vec3& Math::vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Math::vec3 Math::vec3::operator-(const vec3& v) {
    return { x - v.x, y - v.y, z - v.z };
}

Math::vec3& Math::vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Math::vec3 Math::vec3::operator*(double scale) {
    return { x * scale, y * scale, z * scale };
}

Math::vec3& Math::vec3::operator*=(double scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Math::vec3 Math::vec3::operator/(double divisor) {
    return { x * divisor, y * divisor, z * divisor };
}

Math::vec3& Math::vec3::operator/=(double divisor) {
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

Math::vec3 Math::operator*(double scale, const Math::vec3& v) {
    return Math::vec3(scale * v.x, scale * v.y, scale * v.z);
}



bool Math::ivec3::operator==(const ivec3& v) {
    return (x == v.x && y == v.y && z == v.z);
}

bool Math::ivec3::operator!=(const ivec3& v) {
    return (x != v.x || y != v.y || z != v.z);
}

Math::ivec3 Math::ivec3::operator+(const ivec3& v) {
    return { x + v.x, y + v.y, z + v.z };
}

Math::ivec3& Math::ivec3::operator+=(const ivec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Math::ivec3 Math::ivec3::operator-(const ivec3& v) {
    return { x - v.x, y - v.y, z - v.z };
}

Math::ivec3& Math::ivec3::operator-=(const ivec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Math::ivec3 Math::ivec3::operator*(int scale) {
    return { x * scale, y * scale, z * scale };
}

Math::ivec3& Math::ivec3::operator*=(int scale) {
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Math::ivec3 Math::ivec3::operator/(int divisor) {
    return { x / divisor, y / divisor, z / divisor };
}

Math::ivec3& Math::ivec3::operator/=(int divisor) {
    x /= divisor;
    y /= divisor;
    z /= divisor;
    return *this;
}

Math::vec3 Math::ivec3::operator* (double scale) {
    return { x * scale, y * scale, z * scale };
}

Math::vec3 Math::ivec3::operator/ (double divisor) {
    return { x / divisor, y / divisor, z / divisor };
}