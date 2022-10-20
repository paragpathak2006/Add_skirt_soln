#pragma once
#include "Header.h"
#include "Point.h"
class Cubic
{
public:
    Point P[2];
    Point T[2];
    Cubic() {};
    Cubic(Point P0, Point P1, Point N0, Point N1, double slope) {
        P[0] = P0;  T[0] = N0 * slope;
        P[1] = P1;  T[1] = N1 * slope;
    }

    Point point(double u) {
        auto u2 = u * u;                        auto u3 = u2 * u;
        auto B0 = 1 - 3 * u2 + 2 * u3;          auto B1 = 3*u2 - 2 * u3;
        auto B2 = u - 2*u2 + u3;                auto B3 = -u2 + u3;
        return P[0] * B0 + P[1] * B1 + T[0] * B2 - T[1] * B3;
    }

    Point point(int i) { return point(i / 100.0); }

};

