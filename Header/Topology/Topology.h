#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../Header.h"
#include "Edge.h"
#include "Node.h"
#include "Loop.h"
#include "Face.h"

#include "../STL/stl.h"
#include "../IO/Finder.h"
#include "../IO/output_console.h"
using namespace std;
using namespace stl_reader;

int cycle(int i);
class Topology {

public:

    Tessellation mesh;
    Nodes nodes;
    Edges edges;
    Loop inner_loop;

    Topology(string file,string type);

    void read_file_txt(string file);
    void read_file_stl(string file);
    void add_face(Point P0, Point P1, Point P2, Point N);
    void rotate1(const float* c, float& x, float& y, float& z);

    void generate_topology();
    void create_nodal_topology();
    void create_edge_topology();
    void add_new_edge(Face& face, int ii, Edges& edges, int& edge_index);
    void add_new_node(Face& face, int ii, Nodes& nodes, int& node_index);
    void set_edge(Face& face, int edge_index, Edges& edges);

    void extract_tessalation_boundary();
    void extract_tessalation_boundary(int start_edge);

    int get_first_boundary_edge();

};

