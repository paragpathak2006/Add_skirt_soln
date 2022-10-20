#pragma once

#include "Elements.h"
#include "Loop.h"
#include "helpers.h"
#include "Topology.h"
#include <iostream>
using namespace std;
#include "Parameters.h"
class Wireframe {

    public:
        Loop inner_loop, outter_loop;

        Wireframe(Topology& part, Parameters params) {
            cout << endl << endl << "---------inner_loop-------------" << endl << endl;

            inner_loop = part.inner_loop;
#ifdef DEBUG
            inner_loop.print(cout);
#endif


            cout << endl << endl << "---------outter_loop-------------" << endl << endl;

            outter_loop.build_outer_loop(inner_loop, part.nodes, params);
#ifdef DEBUG
            outter_loop.print(cout);
            cout <<"Updated Nodes List: \n" << part.nodes;
            cout << "\n\nSprawl : \n";
            for (int i = 0; i < outter_loop.nodes.size(); i++)
                cout << part.nodes[inner_loop.nodes[i]] <<" + " << inner_loop.tangents[i] << " -> " << part.nodes[outter_loop.nodes[i]] <<" + " << outter_loop.tangents[i] << endl;
#endif

        }
};

