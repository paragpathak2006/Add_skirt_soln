#pragma once

#include "Header.h"
#include <vector>
#include <iostream>
using namespace std;
#include "Point.h"
#include "Face.h"

#include <iostream>
#include "output_console.h"

class Edge {

public:
    int index = 0;
    int node[2] = { -1,-1 };
    int traingle[2] = { -1,-1 };
    typedef Point Normal;
    typedef Point Tangent;

    Normal N;
    Tangent T;

    ostream& print(ostream& c) {
        c << "Edge " << index;
        c << " | Normal : " << N;
        c << " | Tangent: " << T;
        c << print2(c, " | Node", node);
        c << print2(c, " | Face", traingle);
        return c;
    }


    Edge(int i, int j) { 
        node[0] = i;
        node[1] = j;  
    }
    Edge(int edge_index, int i, int j, int ti, int tj, Normal n, Nodes& node_set)    {
        node[0] = i;            traingle[0] = ti;   
        node[1] = j;            traingle[1] = tj;
        index = edge_index;     N = n;
    }

    void setEdge(int edge_index, int ti, int tj, Normal n) {
        traingle[0] = ti;   traingle[1] = tj;        index = edge_index;        N = n;
    }
    void tangent(Point P0, Point P1) {        T = (P1 - P0) * N;    }

    int get_opposite_face(int current_face) {
        if (traingle[0] != current_face)            return traingle[0];
        else                                        return traingle[1];
    }

    int get_opposite_node(int current_node) {
        if (node[0] != current_node)            return node[0];
        else                                    return node[1];
    }

    int cycle_boundary_edges(int pivot, Faces& faces, Edges edges) {
        int next_edge = index;
        int current_face = get_opposite_face(-1);

        for (int i = 0; i < 20; i++) {
            next_edge = edges[next_edge].next_edge(pivot, current_face, faces);
            current_face = edges[next_edge].get_opposite_face(current_face);
            if (current_face == -1) break;
        }
        return next_edge;
    }


    int next_edge(int pivot, int current_face, Faces& faces) {

        int opposite_pivot = get_opposite_node(pivot);

        Face next_face = faces[current_face];
        int i = 0;
        for (i = 0; i < 3; i++)
            if (next_face.node[i] == opposite_pivot) break;

        return next_face.edge[i];
    }


    bool operator==(Edge& E) { return  node[0] == E.node[0] && node[1] == E.node[1]; }

};

bool is_edge_connected(int A1, int A2, int B1, int B2);
bool is_edge_connected(Edge E1, Edge E2);



