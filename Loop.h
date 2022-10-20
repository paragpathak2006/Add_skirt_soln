#pragma once

#include <vector>
#include <cmath>
#include <tuple>
using namespace std;

#include "Header.h"
#include "Edge.h"
#include "Node.h"
#include "output_console.h"
#include <iostream>
#define PI 3.14159265358979323846
#define RAD_TO_DEG 180/PI
#include <cmath>
#include "Parameters.h"
class Loop
{
public:

    Edges edges;
    Node_List nodes;
    Tangents tangents;
    Parameters params;

    void print(ostream& c) { print_edges(c);print_nodes(c);    print_tangents(c);    }
    void print_edges(ostream& c) {    c <<"Loop : Edges : \n" << edges<<endl; }
    void print_nodes(ostream& c) {    c << "Loop : Nodes: \n" << nodes << endl; }
    void print_tangents(ostream& c) { c << "Loop : Tangents : \n" << tangents << endl; }
    int next_edge_index(int i) { if (i == edges.size() - 1) return 0; return i + 1; }
    void build_outer_loop(Loop& inner_loop, Nodes& node_set, Parameters p) {
        params = p;
        tangents = inner_loop.tangents;
        add_nodes(inner_loop.nodes, node_set);
        project(node_set);
        sprawl(node_set);
        reverse_tangents();
    }

    int get_angle_num_nodes(int i, int j) {
        auto Ti = edges[i].T.normalize();        auto anglei = atan2(Ti.y, Ti.x) * RAD_TO_DEG;
        auto Tj = edges[j].T.normalize();        auto anglej = atan2(Tj.y, Tj.x) * RAD_TO_DEG;
        auto diff = anglej - anglei;

        if (diff < 0)   diff = diff + 360;
        if (diff > 360) diff = diff - 360;

        int num_nodes = 1;
        if (diff >= params.min_angle) 
            num_nodes = floor(diff / params.min_angle) + 1;

        return num_nodes;
    }


    void get_tangents(int i, int j, int num_nodes) {
        auto Ti = edges[i].T.normalize();        
        auto Tj = edges[j].T.normalize();        

        if (num_nodes <= 1) {
            auto tangent = (Ti  + Tj) / 2;
            tangents.push_back(tangent);
            return;
        }

        auto size = num_nodes - 1;
        for (int i_node = 0; i_node <= size; i_node++)
        {
            float ai = (size - i_node) / (float)size;
            float aj = i_node / (float)size;

            auto tangent = (Ti * ai + Tj * aj);
            tangent.normalize();
            tangents.push_back(tangent);
        }
    }

    void get_node_list(int i, int j, int num_nodes) {
        Node_List node_list;
        if (num_nodes <= 1) {
            nodes.push_back(edges[i].node[1]);
            return;
        }
        for (int i_node = 0; i_node < num_nodes; i_node++)
            nodes.push_back(edges[i].node[1]);
    }



    void create_nodes_and_tangents() {
        for (int i = 0; i < edges.size(); i++) 
        {
            auto j = next_edge_index(i);
            int num_nodes = get_angle_num_nodes(i, j);
            get_node_list(i, j, num_nodes);
            get_tangents(i, j, num_nodes);
        }

    }

    void add_nodes(Node_List& inp_nodes, Nodes& node_set) {
        for (auto it = inp_nodes.begin(); it != inp_nodes.end(); ++it) {
            int last_index = node_set.size();
            Node node(last_index, node_set[*it].point());
            node_set.push_back(node);
            nodes.push_back(last_index);
        }
    }

    void reverse_tangents() {
        for (auto it = tangents.begin(); it != tangents.end(); ++it) {
            it->x = -it->x;
            it->y = -it->y;
        }
    }


    void project(Nodes& node_set) { 
        for (int i = 0; i < nodes.size(); i++) 
            node_set[nodes[i]].z = 0;

        for (auto& tangent : tangents)
            tangent.z = 0.0;
    }

    void sprawl(Nodes& node_set) { 
        for (int i = 0; i < nodes.size(); i++) {

            Point p = tangents[i] * params.sprawl;
            node_set[nodes[i]].translate(p);

        }
    }

    //void grow(Nodes& boundary) {                for (Node& P : boundary)            P.z = 0;    }
    //void smoothen(Nodes& boundary) {            for (Node& P : boundary)            P.z = 0;    }
    //void smoothen_shape(Nodes& shape) {         for (Node& P : shape)            P.z = 0;    }

};


//for (int i = 0; i < nodes.size(); i++)
//{
//    Node N0 = node_set[nodes[i - 1]];         auto P0 = Vector2D(N0.x, N0.y);
//    Node N1 = node_set[nodes[i]];             auto P1 = Vector2D(N1.x, N1.y);
//    Node N2 = node_set[nodes[i + 1]];         auto P2 = Vector2D(N2.x, N2.y);
//
//    auto normal = P1.get_normal(P0, P2);
//    P1.translate(normal);
//};

//void get_tangents(Nodes& node_set) {
//    for (int i = 0; i < nodes.size(); i++)
//    {
//        auto P0 = node_set[nodes[i - 1]].point();
//        auto P1 = node_set[nodes[i]].point();
//        auto P2 = node_set[nodes[i + 1]].point();

//        auto tangent = P1.get_normal(P0, P2);
//        tangents.push_back(tangent);
//    }
//}

//void create_inner_loop_from_tessalation(Edges& tessalation_edges, Nodes& node_set) {
//    for (Edge edge : tessalation_edges)
//        if (edge.traingle[1] == -1)
//            edges.push_back(edge);
//
//    get_boundary_nodes(node_set);
//    get_tangents(node_set);
//}
//

    //void get_boundary_nodes(Nodes& node_set) {
    //    int tip_node = edges[0].node[0];
    //    nodes.push_back(tip_node);
    //    for (Edge edge : edges)
    //    {
    //        if (edge.node[0] != tip_node)
    //            tip_node = edge.node[0];

    //        else if (edge.node[1] != tip_node)
    //            tip_node = edge.node[1];

    //        nodes.push_back(tip_node);
    //    }
    //}

//void sort_loop() {
//    auto unordered_boundary = edges;
//    edges.clear();

//    int tip_node = unordered_boundary[0].node[0];
//    int tip_edge = unordered_boundary[0].index;

//    edges.push_back(unordered_boundary[0]);
//    while (edges.size() < unordered_boundary.size())
//    {
//        for (Edge unordered_edge : unordered_boundary) {
//            bool node_cond0 = unordered_edge.node[0] == tip_node;
//            bool node_cond1 = unordered_edge.node[1] == tip_node;
//            bool edge_cond = tip_edge != unordered_edge.index;

//            if ((node_cond0 || node_cond1) && edge_cond)
//            {
//                tip_edge = unordered_edge.index;
//                if (node_cond0) tip_node = unordered_edge.node[0];
//                if (node_cond1) tip_node = unordered_edge.node[1];

//                edges.push_back(unordered_edge);
//                break;
//            }
//        }
//    }
//}


