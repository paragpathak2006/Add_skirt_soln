#include "output_console.h"
#include "Point.h"
#include "Node.h"
#include "Face.h"
#include "Edge.h"

ostream& operator<<(ostream& c1, ostream& c2) { return c1; }

template<class T> ostream& print3(ostream& c, string name, T p[2]) {    return c << name << "[" << p[0] << "," << p[1] << "," << p[2] << "]";}
template<class T> ostream& print2(ostream& c, string name, T p[1]) {    return c << name << "[" << p[0] << "," << p[1] << "]";}
template<class T> ostream& print(ostream& c, string name, T* p, int size) { 	c << name << "[";	for (int i = 0; i < size; i++) c << p[i] << "],[";	return c << "] ";}

ostream& operator<<(ostream& c, Point& p) { return p.print(c); }
ostream& operator<<(ostream& c, Node& p) { return p.print(c); }
ostream& operator<<(ostream& c, Face& p) { return p.print(c); }
ostream& operator<<(ostream& c, Edge& p) { return p.print(c); }

ofstream& operator<<(ofstream& c, Face& p) { return p.print(c); }

ostream& operator<<(ostream& c, Points& points) { for (Point& point : points) c << point << endl;	return c; }
ostream& operator<<(ostream& c, Nodes& nodes) { for (Node& node : nodes) c << node << endl;	return c; }
ostream& operator<<(ostream& c, Faces& faces) { for (Face& face : faces) c << face << endl;	return c; }
ostream& operator<<(ostream& c, Edges& edges) { for (Edge& edge : edges) c << edge << endl;	return c; }
ostream& operator<<(ostream& c, Indices& Integers) { for (int& i: Integers) c << i << endl;	return c; }

ofstream& operator<<(ofstream& c, Faces& faces) { for (Face& face : faces) c << face << endl;	return c; }
