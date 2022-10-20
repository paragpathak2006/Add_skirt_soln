#pragma once
#include "Header.h"
#include "Point.h"
class Vector2D {
public:
    float x = 0, y = 0;
    Vector2D(float X, float Y) : x(X), y(Y) {}
    Vector2D(Point P) : x(P.x), y(P.y) {}
    Vector2D operator+(Vector2D rhs) { return Vector2D(x + rhs.x, y + rhs.y); }
    Vector2D operator-(Vector2D rhs) { return Vector2D(x - rhs.x, y - rhs.y); }
    Vector2D operator/(double d) { return Vector2D(x / d, y / d); }
    Vector2D operator*(double d) { return Vector2D(x * d, y * d); }
    double operator*(Vector2D rhs) { return (x * rhs.y - y * rhs.x); }
    int sense(Vector2D lhs, Vector2D rhs) {
        if (lhs * rhs > 0) return 1;
        if (lhs * rhs < 0) return -1;
        if (lhs * rhs == 0) return 0;
    }
    Vector2D rotate_90(Vector2D v) { return Vector2D(-v.y, v.x); }
    Vector2D get_normal(Vector2D P1, Vector2D P3) {
        int s = sense(*this - P1, P3 - *this);
        return rotate_90(P3 - P1) * s / 2.0;
    }

    void translate(Vector2D v) { x += v.x; y += v.y; }
};


