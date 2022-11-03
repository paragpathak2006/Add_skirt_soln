#pragma once

#include <tuple>
#include "../Header.h"
#include "Parameters.h"
#include "../Topology/Edge.h"
#include "../Topology/Node.h"
typedef long long int Lint;
typedef Lint Key;
typedef pair<int, int> Node_Pair;
typedef vector<Lint> Octet;

#define TOLERENCE Parameters::tolerence
#define sq(N, P, x) (N.x - P.x) * (N.x - P.x) 
#define d(N, P) sq(N, P, x) + sq(N, P, y) + sq(N, P, z) 
#define is_near_by(N, P) d(N, P) <= TOLERENCE 
#define EDGE_NOT_FOUND -1
#define NODE_NOT_FOUND -1

#define FORI(i) for(int i = 0; i < 3 ;i++)
#define FOR(i,j,k) FORI(i)FORI(j)FORI(k)
#define octet(i,j,k) oct[i + 3*j + 9*k]
#define for_range(it,range) for(auto& it = range.first; it != range.second; ++it)
#define return_index(index) return index; }

// Point Hash functor
struct Hash_of_Point {
    size_t operator() (const Point& P) const {
        constexpr int order = 1e3;
        int Px = round(P.x * order);
        int Py = round(P.y * order);
        int Pz = round(P.z * order);
        return (Px * 18397) + (Py * 20483) + (Pz * 29303);
    }
};

// Point Equal functor
struct Equal_of_Point {
    bool operator()(const Point& P1, const Point& P2) const { 
        return is_near_by(P1, P2); }
};


// Edge Hash functor
struct Hash_of_Edge {
    size_t operator() (const Edge& P) const {
        auto n0 = P.node[0];
        auto n1 = P.node[1];
        if (n0 < n1) return n0 * 18397 + n1 * 20483;
                     return n1 * 18397 + n0 * 20483;
    }
};

// Edge Equal functor
struct Equal_of_Edge {
    bool operator()(const Edge& P1, const Edge& P2) const {
        auto a0 = P1.node[0];        auto a1 = P1.node[1];
        auto b0 = P2.node[0];        auto b1 = P2.node[1];

        if (a0 == b0 && a1 == b1) return true;
        if (a1 == b0 && a0 == b1) return true;

        return false;
    }
};

//typedef unordered_map< Point, Points> Point_Hash;
//typedef unordered_map< Point, Nodes > Node_Hash;

typedef unordered_multimap< Point, int, Hash_of_Point, Equal_of_Point> Point_Hash;
typedef unordered_multimap< Edge, int, Hash_of_Edge, Equal_of_Edge> Edge_Hash;



class Finder {
public:
    static Point_Hash point_hash;
    static Edge_Hash edge_hash;
    static Lint oct[27];

    static void add_point(Point& P, int index)    { point_hash.emplace(P, index); }
    static void add_edge(int i, int j, int index) {  edge_hash.emplace(Edge(i, j), index); }

    static void initialize_hash(int node_num, int edge_num) {
        //FOR(i, j, k) octet(i, j, k) = hasher(i-1, j - 1, k-1);
        point_hash.reserve(node_num);
        edge_hash.reserve(edge_num); 
    }

    static int lookup_point(Nodes& nodes, Point& P) {
        //auto hash_P = hasher(P);
        //auto hash_value = hash_P + octet(i, j, k);//Using memonization
        auto count = point_hash.count(P);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
        if (count > 0) {
            auto range = point_hash.equal_range(P);

            for_range(it, range) {
                int node_index = it->second;
                if (is_near_by(nodes[node_index], P))
                    return node_index;
            }
        }

        add_point(P, nodes.size());
        return NODE_NOT_FOUND;
    }

    static int lookup_edge(Edges& edges, int n1, int n2) 
    {
//        Lint hash_value = edge_hasher(n1,n2);
        int count = edge_hash.count(Edge(n1,n2));

        if (count > 0) {
            auto range = edge_hash.equal_range(Edge(n1, n2));
            for_range(it, range) {
                int edge_index = it->second;
                if (is_edge_equal(edges[edge_index], n1, n2))
                        return edge_index;
            }
        }

        add_edge(n1, n2, edges.size());
        return EDGE_NOT_FOUND;
    }

    static int lookup_point_n2(Nodes& nodes, Point& P) {
        for (auto& node : nodes)
            if (is_near_by(node, P))
                return node.index;

        return NODE_NOT_FOUND;
    }

    static int lookup_edge_n2(Edges& edges, int n1, int n2) {
        for (auto& edge : edges)
            if (is_edge_equal(edge, n1, n2))
                return edge.index;

        return EDGE_NOT_FOUND;
    }


    //------x------x------x------x------x------x------x------x------
    //static Key edge_hasher(int i, int j) { if (i < j)return i * 18397 + j * 20483;return j * 18397 + i * 20483; }

    //static Key hasher(Point& P) { return hasher(P, 0, 0, 0); }
    //static Key hasher(int Px, int Py, int Pz) { return (Px * 18397) + (Py * 20483) + (Pz * 29303); }
    //static Key hasher(Point& P, int i, int j, int k) {
    //    constexpr int order = 1e3;
    //    int Px = floor(P.x * order) + i;
    //    int Py = floor(P.y * order) + j;
    //    int Pz = floor(P.z * order) + k;
    //    Key key = hasher(Px, Py, Pz);
    //    return key;
    //}

    static bool is_edge_equal(Edge& E1, Edge& E2) { return is_edge_equal(E1.node[0], E1.node[1], E2.node[0], E2.node[1]); }
    static bool is_edge_equal(Edge& E, int B1, int B2) { return is_edge_equal(E.node[0], E.node[1], B1, B2); }
    static bool is_edge_equal(int A1, int A2, int B1, int B2) { if (A1 == B1 && A2 == B2) return true;if (A1 == B2 && A2 == B1) return true;return false; }



};


//template <>
//class hash<Point> {
//    size_t operator()(Point P) { return Finder::hasher(P); }
//};


//void build_edge_hash(Edges &edges, Edge_Set &edge_set) {
//    edge_set.reserve(2 * edge_set.size());
//    for (Edge edge : edges)
//        edge_set.emplace(make_pair(edge.node[0], edge.node[1]));
//}

