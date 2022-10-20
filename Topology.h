#pragma once
#include "Header.h"
#include "stl.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
using namespace stl_reader;

int cycle(int i);

#include "Edge.h"
#include "Node.h"
#include "Loop.h"
#include "Face.h"
#include "Finder.h"
#include "output_console.h"
class Topology {

public:

    Tessellation mesh;
    Nodes nodes;
    Edges edges;
    Loop inner_loop;

    Topology();

    void read_file_txt(string file);
    void read_file_stl(string s);
    void add_face(Point P0, Point P1, Point P2, Point N);
    void rotate1(const float* c, float& x, float& y, float& z);

    void generate_topology();
    void create_nodal_topology();
    void create_edge_topology();

    void extract_tessalation_boundary();
    int get_first_boundary_edge();
    void extract_tessalation_boundary(int start_edge);

};

