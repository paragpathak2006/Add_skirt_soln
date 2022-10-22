#pragma once

#include <tuple>
#include "../Header.h"
#include "Parameters.h"
#include "../Topology/Edge.h"
#include "../Topology/Node.h"
template<class T, class W> double d(T& N, W& P) { return (N.x - P.x) * (N.x - P.x) + (N.y - P.y) * (N.y - P.y) + (N.z - P.z) * (N.z - P.z); }
template<class T, class W> bool is_near_by(T& N, W& P) { return d(N, P) <= Parameters::tolerence; }
typedef long long int Lint;
typedef Lint Key;
typedef pair<int, int> Node_Pair;

typedef unordered_multimap< Key, int> Point_Hash;
typedef unordered_multimap< Key, int> Edge_Hash;
typedef unordered_map< Key , Points> Multi_Point_Hash;
typedef unordered_map< Key , Nodes > Multi_Node_Hash;

class Finder {
public:
    static Point_Hash point_hash;
    static Edge_Hash edge_hash;

    static Key hasher(int Px,int Py, int Pz) {
        return (Px * 18397) + (Py * 20483) + (Pz * 29303);
    }
    static Key edge_hasher(int i, int j) {
        if (i<j)
        return i * 18397 + j * 20483;
        return j * 18397 + i * 20483;
    }

    static Key hasher(Point& P, int i, int j, int k ) { 
        constexpr int order = 1e3;
        int Px = floor(P.x * order) + i;
        int Py = floor(P.y * order) + j;
        int Pz = floor(P.z * order) + k;
        Key key = hasher(Px, Py, Pz);
        //cout << key<<"(" << P.x << "," << P.y << "," << P.z<<")\t";
        return key;
    }
    static Key hasher(Point& P) {return hasher(P, 0, 0, 0);}
    static void add_point(Point& P, int index) {
        vector<int> range = { 0,1 };
        for(int& i : range)
            for (int& j : range)
                for (int& k : range)
                    point_hash.emplace(hasher(P, i,  j,  k), index);
        //cout << endl;
    }

    static auto loop_up_point(Point& P) {
        vector<int> range = { 0,1 };
        for (int& i : range) {
            for (int& j : range){
                for (int& k : range){
                    auto it = point_hash.find(hasher(P, i, j, k));
                    if (it != point_hash.end()) return it;
                }
            }
        }
        return point_hash.end();
        //cout << endl;
    }


    static void add_edge(int i, int j,int index) {
           edge_hash.emplace(edge_hasher(i, j), index);
    }

    static void initialize_hash(int node_num, int edge_num) {
        point_hash.reserve(node_num);
        edge_hash.reserve(edge_num);
    }

    static int find_node_index_of_point(Nodes& nodes, Point& P) {

        //for (auto& node: nodes)
        //    if (is_near_by(node, P))
        //        return node.index;
        //cout << endl <<" Look up : " << P << endl;
        auto hash_point = hasher(P);
        auto found = loop_up_point(P);
        if (found == point_hash.end()){
            //cout << " Add point: " << P << endl;
            add_point(P, nodes.size());
            //cout << point_hash.size() << endl;
            return -1;
        }

        else {
            auto range = point_hash.equal_range(hash_point);
            for (auto it = range.first; it != range.second; ++it) {
                int node_index = it->second;
                if(is_near_by(nodes[node_index], P))return node_index;
                //cout <<"key : "<< it->first << "\t node index : " << it->second << endl;
            }
 
        }

        //cout << " Add point: " << P << endl;
        add_point(P, nodes.size());
        return -1;

    }

    static int find_edge_index_of_node_pair(Edges& edges, int n1, int n2) {
            //for (auto& edge : edges)
            //    if (is_edge_equal(edge, n1, n2))
            //        return edge.index;
        auto hash_edge = edge_hasher(n1,n2);
        auto found = edge_hash.find(hash_edge);
        if (found == edge_hash.end()) {add_edge(n1 , n2, edges.size());return -1;}
        else {
            auto range = edge_hash.equal_range(hash_edge);
            for (auto it = range.first; it != range.second; ++it) {
                int edge_index = it->second;
                auto en1 = edges[edge_index].node[0];
                auto en2 = edges[edge_index].node[1];
                if (en1 == n1 && en2 == n2)                    return edge_index;
                if (en1 == n2 && en2 == n1)                    return edge_index;
            }
        }

        add_edge(n1, n2, edges.size());
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

