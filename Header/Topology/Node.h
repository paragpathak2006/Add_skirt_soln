#pragma once
#include <iostream>
#include "../Header.h"
#include "../Geometry/Point.h"
#include "../IO/output_console.h"

class Node {
public:
    int index = -1;
    double x = 0, y = 0, z = 0;
    Node() { x = 0; y = 0; z = 0;index = -1;}
    Node(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    Node(int i, double X, double Y, double Z) : index(i), x(X), y(Y), z(Z) {}
    Node(int i, Point P) {  index = i; x = P.x; y = P.y; z = P.z; }
    void set(int i, Point& P){ index = i; x = P.x; y = P.y; z = P.z; }
    Point point() { return Point(x, y, z); }
    void translate(Point& v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    ostream& print(ostream& c) {
        return c << index<<":" << "(" << x << " , " << y << " , " << z << " )";
    }

};

