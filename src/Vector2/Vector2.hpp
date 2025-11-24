#pragma once
#include<iostream>

class Vector2 {
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(const Vector2& other);
    float getX() const;
    float getY() const;
    void setX(float x) { this->x = x; }
    void setY(float y) { this->y = y; }
    Vector2& operator=(const Vector2& other);
    Vector2& operator+=(const Vector2& other);
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    
    ~Vector2();
    
    static const Vector2 ZERO;
    static const Vector2 ONE;
    static const Vector2 UP;
    static const Vector2 DOWN;
    static const Vector2 LEFT;
    static const Vector2 RIGHT;
    
private:
    float x;
    float y;
};