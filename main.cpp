// MachinaLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "Header.h"
#include "Boundary.h"
#include "Topology.h"
#include "Tessellation.h"
#include "Parameters.h"
//namespace convention {
//	typedef vector<Edge> Edges;
//	//typedef vector<Edge> Loop1;
//
//	typedef vector<Face> Faces;
//	typedef vector<Face> Tessellation;
//
//	typedef vector<Node> Nodes;
//	typedef vector<Cubic> Curves;
//
//	typedef vector<Point> Points;
//	typedef vector<Point> Vectors;
//	typedef vector<Point> Normals;
//	typedef vector<Point> Tangents;
//
//	typedef Point Normal;
//	typedef Point Tangent;
//
//
//	typedef vector<int> Edge_List;
//	typedef vector<int> Node_List;
//	typedef vector<int> Face_List;
//	typedef vector<int> Edge_List;
//
//};

double tolerence = 1e-5;

int main()
{
    int step = 10;
    double slope = 4;
    double min_angle = 10;
    double sprawl = 4;
    Parameters params(step, slope,min_angle, sprawl);
    Topology part;
    Wireframe frame(part, params);
    Skirt skirt(frame, part.nodes, params, part.mesh);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
