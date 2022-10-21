#include "../../Header/Topology/Edge.h"

bool is_edge_connected(int A1, int A2, int B1, int B2) { if (A1 == B1 && A2 != B2) return true;    if (A2 == B2 && A1 != B1) return true;    if (A2 == B1 && A1 != B2) return true;    if (A1 == B2 && A2 != B1) return true;    return false; }
bool is_edge_connected(Edge E1, Edge E2) {
    int A1 = E1.node[0];    int A2 = E1.node[1];
    int B1 = E1.node[0];    int B2 = E1.node[1];
    return is_edge_connected(A1, A2, B1, B2);
}
