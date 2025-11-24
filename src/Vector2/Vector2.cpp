#include "Vector2.hpp"

const Vector2 Vector2::ZERO = Vector2(0.f, 0.f);
const Vector2 Vector2::ONE = Vector2(1.f, 1.f);
const Vector2 Vector2::UP = Vector2(0.f, -1.f);
const Vector2 Vector2::DOWN = Vector2(0.f, 1.f);
const Vector2 Vector2::LEFT = Vector2(-1.f, 0.f);
const Vector2 Vector2::RIGHT = Vector2(1.f, 0.f);

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(const Vector2& other) : x(other.x), y(other.y) {}

float Vector2::getX() const {
    return x;
}

float Vector2::getY() const {
    return y;
}

Vector2& Vector2::operator=(const Vector2& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return Vector2(x / scalar, y / scalar);
}

Vector2::~Vector2() {}