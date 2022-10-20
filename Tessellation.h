#pragma once
#include "Header.h"
#include "stl.h"
#include "Cubic.h"
#include "Boundary.h"
#include <string>
#include <fstream>
#include <iostream>
#include "output_console.h"
#include "stl_interface.h"
#include "Parameters.h"
class Skirt {

public:
    Tessellation skirt;
    Curves curves;
    Parameters params;

    Skirt(Wireframe& boundary, Nodes& node, Parameters p, Tessellation part) {
        cout << "\n\nSkirt : \n" ;
        params = p;
        tessalation_curves(boundary, node);
        tessalate();

#ifdef DEBUG
//        ofstream fout("skirt.txt");        
 //       cout << "\n\n" << skirt;        fout << skirt;
#endif
        //stl_interface out(skirt, "skirt.stl");
        stl_interface::write_stl("skirt.stl", skirt);
        stl_interface::write_stl("part.stl", part);
        stl_interface::write_stl("skirt-part.stl", part,skirt);

    }

    void tessalation_curves(Wireframe& boundary, Nodes& node) {

        for (int i = 0; i < boundary.outter_loop.nodes.size(); i++)
        {
            Point P0 = node[boundary.inner_loop.nodes[i]].point();
            Point P1 = node[boundary.outter_loop.nodes[i]].point();

            Tangent T0 = boundary.inner_loop.tangents[i];
            Tangent T1 = boundary.outter_loop.tangents[i];
            curves.push_back(Cubic(P0, P1, T0, T1, params.slope));
        };
    }

    void tessalate() {

        for (int i = 0; i < curves.size(); i++)
        {
            int j = i + 1; if (j == curves.size()) j = 0;

            Cubic C1 = curves[i];
            Cubic C2 = curves[j];

            tessalate(C1, C2);
        };
    }

    void tessalate(Cubic& A, Cubic& B) {
  

        for (int i = 0; i < 100; i = i + params.step)
        {
            auto A0 = A.point(i);        auto A1 = A.point(i + params.step);
            auto B0 = B.point(i);        auto B1 = B.point(i + params.step);

            if ( i == 100 && A.P[1] == B.P[1])
                tessalate(A0, B0, B1);

            else
                tessalate(A0, B0, A1, B1);
        }
    }

    void tessalate(Point A0, Point B0, Point A1, Point B1) {
        tessalate(A0, A1, B1);
        tessalate(A0, B0, B1);
    }

    void tessalate(Point P0, Point P1, Point P2) {
        skirt.push_back(Face(skirt.size(),P0, P1, P2));
    }

};
