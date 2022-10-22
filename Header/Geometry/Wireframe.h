#pragma once
#include <iostream>
#include "../Header.h"
#include "../Elements.h"
#include "../helpers.h"
#include "../Topology/Loop.h"
#include "../Topology/Topology.h"
#include "../IO/Parameters.h"
using namespace std;
class Wireframe {

    public:
        Loop inner_loop, outter_loop;

        Wireframe(Topology& part) {
            inner_loop = part.inner_loop;
            outter_loop.build_outer_loop(inner_loop, part.nodes);
            print_outter_loop(part);
        }

        void print_outter_loop(Topology& part) {

        #ifdef DEBUG
            cout << endl << endl << "---------inner_loop-------------" << endl << endl;
            inner_loop.print_tangents(cout);
            inner_loop.print_nodes(cout, part.nodes);

            cout << endl << endl << "---------outter_loop-------------" << endl << endl;
            outter_loop.print_edges(cout);
            outter_loop.print_tangents(cout);
            outter_loop.print_nodes(cout, part.nodes);
            cout << "Updated Nodes List: \n" << part.nodes;
            cout << "\n\nSprawl : \n";
            for (int i = 0; i < outter_loop.nodes.size(); i++)
                cout << part.nodes[inner_loop.nodes[i]] << " + " << inner_loop.tangents[i] << " -> " << part.nodes[outter_loop.nodes[i]] << " + " << outter_loop.tangents[i] << endl;
        #endif
        }
};

