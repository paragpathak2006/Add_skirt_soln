#pragma once
#include "Header.h"
#include "Point.h"
#include <iostream>
#include<fstream>
#include "output_console.h"

class Face {
public:
    Normal N;
    Point point[3];

    int index = 0;
    int node[3] = {-1,-1,-1};
    int edge[3] = {-1,-1,-1};

    ostream& print(ostream& c) {
        c << "Face " << index <<" : ";
        c << " | Normal" << N;
        c <<  print3(c, " | Point", point);
        c <<  print3(c, " | Node" , node);
        c <<  print3(c, " | Edge"  , edge);
        //f << point[0].x << " " << point[0].y << " " << point[0].z << " " << endl;
        //f << point[1].x << " " << point[1].y << " " << point[1].z << " " << endl;
        //f << point[2].x << " " << point[2].y << " " << point[2].z << " " << endl;
        //f << point[0].x << " " << point[0].y << " " << point[0].z << " " << endl;

        //f << endl << endl;
        return c;
    }
    ofstream& print(ofstream& f) {
        f << point[0].x << " " << point[0].y << " " << point[0].z << " " << endl;
        f << point[1].x << " " << point[1].y << " " << point[1].z << " " << endl;
        f << point[2].x << " " << point[2].y << " " << point[2].z << " " << endl;
        f << point[0].x << " " << point[0].y << " " << point[0].z << " " << endl; 

        f << endl << endl;
        return f;
    }

    Face() {
        point[0] = Point();
        point[1] = Point();
        point[2] = Point();
        N = Point();
    }

    Face(Point P0, Point P1, Point P2) {
        point[0] = P0;
        point[1] = P1;
        point[2] = P2;
    }

    Face(int i, Point P0, Point P1, Point P2) {
        index = i;
        point[0] = P0;
        point[1] = P1;
        point[2] = P2;
    }


    Face(int i, Point P0, Point P1, Point P2, Normal normal)   {
        index = i;

        point[0] = P0;
        point[1] = P1;        auto P10 = (P1 - P0);
        point[2] = P2;        auto P21 = (P2 - P1);
        
        auto dir = P10 * P21;

        N = normal;
        if (dot(dir, N) < 0) {
            point[1] = P2;
            point[2] = P1;
        }
    }

};
