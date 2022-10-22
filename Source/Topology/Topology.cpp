#include "../../Header/Topology/Topology.h"
int cycle(int i) { if (i + 1 > 2) return 0; return i + 1; }
#include <iostream>
#include "../../Header/IO/Parameters.h"
#include "../../Header/IO/output_console.h"

using namespace std;
Point_Hash Finder::point_hash;
Edge_Hash Finder::edge_hash;
Topology::Topology(string file, string type = "STL") {
    cout << "\n--------------------------------------\n" << endl;
    cout << "Reading file \'"<< file <<"." << type << "\'..." << endl;

    if (type == "txt")      read_file_txt(file);
    else if (type == "STL") read_file_stl(file);
    else if (type == "stl") read_file_stl(file);

    else {
        cout << "Invalid file"<<endl;exit(0);
    }

    cout << "Reading file compleated !" << endl;


    generate_topology();
    extract_tessalation_boundary();
}

void Topology::add_face(Point P0, Point P1, Point P2, Point N) {
    int index = mesh.size();
    mesh.push_back(Face(index, P0, P1, P2, N));
}
void Topology::read_file_txt(string file) {
    ifstream fin(file);
    string s;
    double n0 = 0, n1 = 0, n2 = 0;
    double v0[3] = { 0,0,0 }, v1[3] = { 0,0,0 }, v2[3] = { 0,0,0 };
    int i = 0;
    while (fin >> s) {
        if (s != "normal" && s != "vertex") continue;
        if (s == "normal") { fin >> n0 >> n1 >> n2;
#ifdef DEBUG
        cout << endl << endl << s << " : " << n0 << " , " << n1 << " , " << n2 << endl;
#endif
        }
        if (s == "vertex") 
        {
            fin >> v0[i] >> v1[i] >> v2[i];
#ifdef DEBUG
            cout << s << " : " << v0[i] << " , " << v1[i] << " , " << v2[i] << endl;
#endif
            i++;
        }

        if (i == 3) {
            Point P0(v0[0], v1[0], v2[0]);
            Point P1(v0[1], v1[1], v2[1]);
            Point P2(v0[2], v1[2], v2[2]);
            Normal N(n0, n1, n2);
            add_face(P0, P1, P2, N);
            i = 0;
        }
    }
#ifdef DEBUG
    cout << "read_file-Mesh : " << endl << mesh << endl << endl;
#endif
    fin.close();
}

void Topology::read_file_stl(string file) {
    float x, y, z;
    try {
        StlMesh <float, unsigned int> mesh(file);
        for (size_t itri = 0; itri < mesh.num_tris(); ++itri) {
            Point P[3], N;
            for (size_t icorner = 0; icorner < 3; ++icorner) {
                const float* c = mesh.tri_corner_coords(itri, icorner);
                if (icorner < 3) {rotate1(c,x,y,z);P[icorner] = Point(x, y,  z);}
            }
            const float* n = mesh.tri_normal(itri);
            rotate1(n, x, y, z);
            N = Point(x, y, z);
            add_face(P[0], P[1], P[2], N);
        }
    }
    catch (exception& e) { cout << e.what() << std::endl;exit(0); }

}

void Topology::rotate1(const float* c, float& x, float& y, float& z) {
    x = c[0];    y = -c[2];    z = c[1];
    float x1 = x, y1 = y, z1 = z;

    x = 0.7071068 * x1 + 0.0000000 * y1 + 0.7071068 * z1;
    y = 0.0000000 * x1 + 1.0000000 * y1 + 0.0000000 * z1;
    z = -0.7071068 * x1 + 0.0000000 * y1 + 0.7071068 * z1;

    x = x / 10;    y = y / 10;    z = z / 10;    z = z + 10;
}

void Topology::generate_topology() {
    cout << "\n--------------------------------------\n" << endl;
    cout << "generating nodal topology..." << endl;
    create_nodal_topology();    
    cout << "nodal topology generated" << endl;
    cout << "\n--------------------------------------\n" << endl;
    cout << "generating edge topology..." << endl;
    create_edge_topology();    
    cout << "edge topology generated" << endl;
    cout << "\n--------------------------------------\n" << endl;
}

void Topology::create_nodal_topology() {
    int num_points = 3 * mesh.size();
    int num_edges = 3 * mesh.size();

    Finder::initialize_hash(num_points, num_edges);
    for (auto face = mesh.begin(); face != mesh.end(); ++face) {
        for (int ii = 0; ii < 3; ii++){
            int node_index = Finder::find_node_index_of_point(nodes, face->point[ii]);
            if (node_index == -1) {
                node_index = nodes.size();
                auto node = Node();
                node.set(node_index, face->point[ii]);
                nodes.push_back(node);
            }
            face->node[ii] = node_index;
        }
    }
#ifdef DEBUG
    cout << "create_nodal_topology-Mesh : " << endl << mesh << endl << endl;
#endif
}


void Topology::create_edge_topology() {
    for (auto face = mesh.begin(); face != mesh.end(); ++face) {

        for (int ii = 0; ii < 3; ii++)
        {
            int jj = cycle(ii);
            int kk = cycle(jj);

            int tnode_i = face->node[ii];
            int tnode_j = face->node[jj];

            int edge_index = Finder::find_edge_index_of_node_pair(edges, tnode_i, tnode_j);

            if (edge_index < 0) {
                edge_index = edges.size();
                auto N = face->N;
                auto edge = Edge(tnode_i, tnode_j);
                int tri_index = face->index;
                edge.setEdge(edge_index, tri_index, -1, N);
                edge.tangent(nodes[tnode_i].point(), nodes[tnode_j].point());
                edges.emplace_back(edge);
            }

            else {
                edges[edge_index].traingle[1] = face->index;
            }

            face->edge[kk] = edge_index;
        }
    }
#ifdef DEBUG
    cout << "create_edge_topology-Mesh : " << endl << mesh << endl << endl;
    cout << "create_edge_topology-Edges : " << endl << edges << endl << endl;
#endif

}

void Topology::extract_tessalation_boundary() {
    int start_edge = get_first_boundary_edge();
    extract_tessalation_boundary(start_edge);
    inner_loop.create_nodes_and_tangents();    cout << endl;

#ifdef DEBUG
    inner_loop.print(cout);
#endif
}

//-------------------------------------------------

int Topology::get_first_boundary_edge() {
    int start_edge = -1;

    for (auto& edge : edges)
        if (edge.traingle[1] == -1)
            return edge.index;

    return start_edge;
}

void Topology::extract_tessalation_boundary(int start_edge) {
    int next_edge = start_edge;
    int pivot = edges[next_edge].node[1];
#ifdef DEBUG
    cout << "extract_tessalation_boundary-Edges :" << endl;
#endif

    do{
        next_edge = edges[next_edge].cycle_boundary_edges(pivot, mesh, edges);
        pivot = edges[next_edge].get_opposite_node(pivot);
#ifdef DEBUG
        cout << edges[next_edge] << endl;
#endif
        inner_loop.edges.push_back(edges[next_edge]);
    }
    while (next_edge != start_edge);
}

