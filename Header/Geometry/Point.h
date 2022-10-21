#pragma once
#include <iostream>
#include "../Header.h"
#include "../IO/output_console.h"

Point cross(Point lhs, Point rhs);
double dot(Point lhs, Point rhs);

class Point {
public:
    double x = 0, y = 0, z = 0;
    Point(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    Point() { x = 0; y = 0; z = 0; }
    Point operator+(Point rhs) { return Point(x + rhs.x, y + rhs.y, z + rhs.z); }
    Point operator-(Point rhs) { return Point(x - rhs.x, y - rhs.y, z - rhs.z); }
    Point operator/(double d) { return Point(x / d, y / d, z / d); }
    Point operator*(double d) { return Point(x * d, y * d, z * d); }
    bool operator==(Point rhs) {        return x == rhs.x && y == rhs.y && z == rhs.z;    }
    Point operator*(Point rhs) { return Point(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        ); }

    ostream& print(ostream& c) {        return c << "(" << x << "," << y << "," << z << ")";    }


    //Vector2D rotate_90(Vector2D v) { return Vector2D(-v.y, v.x); }
    //Point get_normal(Point P1, Point P3) {        return (*this * 2 - P1 - P3) * sense(P1, P3) / 2;    }

    //int sense(Point P1, Point P3) {
    //    auto v1 = Vector2D(P1);
    //    auto v2 = Vector2D(*this );
    //    auto v3 = Vector2D(P3);
    //    return v2.sense(v1, v2);
    //}

    void translate(Point& v) { 
        x += v.x; 
        y += v.y;
        z += v.z;    
    }

    Point normalize() {
        double d = sqrt(x * x + y * y + z * z);
        x = x / d;
        y = y / d;
        z = z / d;
        return Point(x, y, z);
    }

    Point unity() {
        double d = sqrt(x * x + y * y + z * z);
        return Point(x / d, y / d, z / d);
    }

};





