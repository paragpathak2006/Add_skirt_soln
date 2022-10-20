#include "Point.h"
Point cross(Point lhs, Point rhs) { return lhs * rhs; }
double dot(Point lhs, Point rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
