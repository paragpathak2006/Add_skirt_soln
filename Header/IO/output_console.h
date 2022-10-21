#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "../Header.h"
using namespace std;

template<class T> ostream& print3(ostream& c, string name, T p[2]);
template<class T> ostream& print2(ostream& c, string name, T p[1]);
template<class T> ostream& print(ostream& c, string name, T* p, int size);


ostream& operator<<(ostream& c1, ostream& c2);
ostream& operator<<(ostream& c, Point& point);
ostream& operator<<(ostream& c, Node& node);
ostream& operator<<(ostream& c, Face& face);
ostream& operator<<(ostream& c, Edge& edge);

ostream& operator<<(ostream& c, Points& points);
ostream& operator<<(ostream& c, Nodes& nodes);
ostream& operator<<(ostream& c, Faces& faces);
ostream& operator<<(ostream& c, Edges& edges);
ostream& operator<<(ostream& c, Indices& Integers);

ofstream& operator<<(ofstream& c, Face& face);

