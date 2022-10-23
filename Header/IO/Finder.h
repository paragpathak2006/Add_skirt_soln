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
typedef vector<Lint> Octet;
typedef unordered_multimap< Key, int> Point_Hash;
typedef unordered_multimap< Key, int> Edge_Hash;
typedef unordered_map< Key , Points> Multi_Point_Hash;
typedef unordered_map< Key , Nodes > Multi_Node_Hash;

#define FORI(i) for(int i = 0; i < 3 ;i++)
#define FOR(i,j,k) FORI(i)FORI(j)FORI(k)
#define O(i,j,k) i + 3*j + 9*k
#define OCTET(i,j,k) octet[O(i, j, k)]
#define FOR_RANGE(it,range) for(auto& it = range.first; it != range.second; ++it)

class Finder {
public:
    static Point_Hash point_hash;
    static Edge_Hash edge_hash;
    static Lint octet[27];

    static void initialize_hash(int node_num, int edge_num) { 
        FOR(i, j, k) OCTET(i, j, k) = hasher(i-1, j - 1, k-1);
        point_hash.reserve(node_num);
        edge_hash.reserve(edge_num); 
    }
    static Key edge_hasher(int i, int j) {if (i<j)return i * 18397 + j * 20483;return j * 18397 + i * 20483;}
    static Key hasher(Point& P) { return hasher(P, 0, 0, 0); }
    static Key hasher(int Px,int Py, int Pz) {return (Px * 18397) + (Py * 20483) + (Pz * 29303);}

    static Key hasher(Point& P, int i, int j, int k ) { 
        constexpr int order = 1e3;

        int Px = floor(P.x * order) + i;
        int Py = floor(P.y * order) + j;
        int Pz = floor(P.z * order) + k;

        Key key = hasher(Px, Py, Pz);
        return key;
    }

    static void add_point(Point& P, int index) { point_hash.emplace(hasher(P), index); }
    static void add_edge(int i, int j, int index) { edge_hash.emplace(edge_hasher(i, j), index); }

    static int lookup_point(Nodes& nodes, Point& P) { for (auto& node : nodes)if (is_near_by(node, P))        return node.index; }
    static int lookup_point_fast(Nodes& nodes, Point& P) {
        auto hash_P = hasher(P);
        FOR(i, j, k)
        {
            auto hash_value = hash_P + OCTET(i, j, k);//Using memonization
            auto count = point_hash.count(hash_value);

            if (count > 0 ) {

                auto range = point_hash.equal_range(hash_value);

                FOR_RANGE(it,range) {

                    int node_index = it->second;

                    if (is_near_by(nodes[node_index], P))
                        return node_index;
                }
            }
        }

        add_point(P, nodes.size());
        return -1;
    }

    static int lookup_edge(Edges& edges, int n1, int n2) { for (auto& edge : edges)if (is_edge_equal(edge, n1, n2))return edge.index; }
    static int lookup_edge_fast(Edges& edges, int n1, int n2) {

        Lint hash_value = edge_hasher(n1,n2);
        int count = edge_hash.count(hash_value);

        if (count > 0) {
            auto range = edge_hash.equal_range(hash_value);
            FOR_RANGE(it,range) {

                int edge_index = it->second;

                if(is_edge_equal(edges[edge_index], n1, n2))
                    return edge_index;
            }
        }

        add_edge(n1, n2, edges.size());
        return -1;
    }

    static bool is_edge_equal(Edge& E1, Edge& E2) { return is_edge_equal(E1.node[0], E1.node[1], E2.node[0], E2.node[1]); }
    static bool is_edge_equal(Edge& E, int B1, int B2) { return is_edge_equal(E.node[0], E.node[1], B1, B2); }
    static bool is_edge_equal(int A1, int A2, int B1, int B2) {if (A1 == B1 && A2 == B2) return true;if (A1 == B2 && A2 == B1) return true;return false;}

};



//void build_edge_hash(Edges &edges, Edge_Set &edge_set) {
//    edge_set.reserve(2 * edge_set.size());
//    for (Edge edge : edges)
//        edge_set.emplace(make_pair(edge.node[0], edge.node[1]));
//}

