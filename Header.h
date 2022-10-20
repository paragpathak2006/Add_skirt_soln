#pragma once
#define DEBUGe
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Face;		class Loop;		class Parameters;
class Topology;	class Node;		class Edge;		
class Skirt;	class Scaffold;	class Finder;
class Point;	class Vector2D;	class Cubic;

typedef unordered_set<pair<int, int>> Edge_Set;
typedef unordered_multimap<int, pair<int, int>> Node_to_Edge_Map;
typedef unordered_map<int, int> Mapping;

typedef vector<Face> Tessellation;
typedef vector<Edge> Edges;		typedef vector<Face> Faces;		typedef vector<Node> Nodes;
typedef vector<Point> Points;	typedef vector<Point> Vectors;	typedef vector<Cubic> Curves;

typedef Point Normal;	typedef vector<Normal> Normals;
typedef Point Tangent;	typedef vector<Tangent> Tangents;

typedef vector<int> Indices;
typedef Indices Edge_List;	typedef Indices Node_List;
typedef Indices Face_List;	typedef Indices Edge_List;

extern double tolerence;

//bool is_next_edge(Edge E1, Edge& E0, int& tip) {    if (E1.node[0] != tip && E1.node[1] != tip)        return false;    if (is_edge_equal(E1, E0)) return false;    if (E1.node[0] == tip) tip = E1.node[0];    if (E1.node[1] == tip) tip = E1.node[1];    return true;}

