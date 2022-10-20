#pragma once

#include <tuple>
#include "Header.h"
#include "Edge.h"
#include "Node.h"
template<class T, class W> double d(T& N, W& P) { return (N.x - P.x) * (N.x - P.x) + (N.y - P.y) * (N.y - P.y) + (N.z - P.z) * (N.z - P.z); }
template<class T, class W> bool is_near_by(T& N, W& P) { return d(N, P) <= tolerence; }
typedef tuple<int, int, int> Index;
typedef pair<int, int> Node_Pair;
typedef unordered_map< Index , int> Point_Hash;
typedef unordered_map< Index , Points> Multi_Point_Hash;
typedef unordered_map< Index , Nodes > Multi_Node_Hash;
typedef unordered_map< Node_Pair, int> Edge_Hash;

class Finder {


public:
    //static Point_Hash point_hash;

    //static int add_point(Point P, int index) {
    //    int Px = floor(P.x * 10000);
    //    int Py = floor(P.y * 10000);
    //    int Pz = floor(P.z * 10000);

    //    for (int i = 0; i < 2; i++)
    //        for (int j = 0; i < 2; i++)
    //            for (int k = 0; i < 2; i++)
    //                int kk = 5;
    //                //point_hash.emplace(make_tuple(P.x + i, P.y + j, P.z + k), index);

    //}

    //static int initialize_point_hash(int n) {
    //    point_hash.reserve(n);
    //}

    static int find_node_index_of_point(Nodes& nodes, Point& P) {
        for (auto& node: nodes)
            if (is_near_by(node, P))
                return node.index;

        return -1;
    }

    static int find_edge_index_of_node_pair(Edges& edges, int n1, int n2) {
            for (auto& edge : edges)
                if (is_edge_equal(edge, n1, n2))
                    return edge.index;

        return -1;
    }

    static bool is_edge_equal(Edge& E1, Edge& E2) { return is_edge_equal(E1.node[0], E1.node[1], E2.node[0], E2.node[1]); }
    static bool is_edge_equal(Edge& E, int B1, int B2) { return is_edge_equal(E.node[0], E.node[1], B1, B2); }
    static bool is_edge_equal(int A1, int A2, int B1, int B2) {
        if (A1 == B1 && A2 == B2) return true;
        if (A1 == B2 && A2 == B1) return true;
        return false;
    }


};



//void build_edge_hash(Edges &edges, Edge_Set &edge_set) {
//    edge_set.reserve(2 * edge_set.size());
//    for (Edge edge : edges)
//        edge_set.emplace(make_pair(edge.node[0], edge.node[1]));
//}

