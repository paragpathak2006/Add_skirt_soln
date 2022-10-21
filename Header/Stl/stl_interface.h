#pragma once
#include <string>
#include "vec3.h"
#include "../Header.h"
#include "triangle.h"
#include "mesh.h"
#include "../Geometry/Point.h"
#include "../Topology/Face.h"

class stl_interface {
public:
    Mesh mesh;

    stl_interface(Tessellation faces) {
        add_mesh(faces);
    }

    stl_interface(Tessellation faces, string s) {
        add_mesh(faces);
        mesh.stl_write(s);
    }


    void add_mesh(Tessellation faces) {
        for (auto& face : faces)
            add_face(face);
    }

    void add_face(Face face) {
        add_face(face.point[0], face.point[0], face.point[0]);
    }

    void add_face(Point& P0, Point& P1, Point& P2) {
        Vec3 p0(P0.x, P0.y, P0.z);
        Vec3 p1(P1.x, P1.y, P1.z);
        Vec3 p2(P2.x, P2.y, P2.z);
        Triangle triangle(p0, p1, p2);
        mesh.add(triangle);
    }

    //void write_stl(string s) {
    //    mesh.stl_write(s);
    //}

    static void write_stl(string filename, Tessellation skirt) {

        //binary file
        string header_info = "solid " + filename + "-output";
        char head[80];
        strncpy_s(head, header_info.c_str(), sizeof(head) - 1);
        char attribute[2] = "0";
        unsigned long nTriLong = skirt.size();

        std::ofstream myfile;

        myfile.open((filename + "-out.stl").c_str(),ios::out | ios::binary);
        myfile.write(head, sizeof(head));
        myfile.write((char*)&nTriLong, 4);

        //write down every triangle
        for (auto it = skirt.begin(); it != skirt.end(); it++) {
            //normal vector coordinates
            //float x = 0, y = 0, z = 0;
            write_point(myfile, it->N);
            write_point(myfile, it->point[0]);
            write_point(myfile, it->point[1]);
            write_point(myfile, it->point[2]);

            //x = it->N.x;            myfile.write((char*)&x, 4);
            //y = it->N.y;            myfile.write((char*)&y, 4);
            //z = it->N.z;            myfile.write((char*)&z, 4);

            ////p1 coordinates
            //x = it->point[0].x;            myfile.write((char*)&x, 4);
            //y = it->point[0].y;            myfile.write((char*)&y, 4);
            //z = it->point[0].z;            myfile.write((char*)&z, 4);

            ////p1 coordinates
            //x = it->point[1].x;            myfile.write((char*)&x, 4);
            //y = it->point[1].y;            myfile.write((char*)&y, 4);
            //z = it->point[1].z;            myfile.write((char*)&z, 4);

            ////p1 coordinates
            //x = it->point[2].x;            myfile.write((char*)&x, 4);
            //y = it->point[2].y;            myfile.write((char*)&y, 4);
            //z = it->point[2].z;            myfile.write((char*)&z, 4);

            myfile.write(attribute, 2);
        }

        //for (auto it = part.begin(); it != part.end(); it++) {
        //    write_point(myfile, it->N);
        //    write_point(myfile, it->point[0]);
        //    write_point(myfile, it->point[1]);
        //    write_point(myfile, it->point[2]);
        //    myfile.write(attribute, 2);
        //}

        myfile.close();
    }


    static void write_stl(string filename, Tessellation skirt , Tessellation part ) {

        //binary file
        string header_info = "solid " + filename + "-output";
        char head[80];
        strncpy_s(head, header_info.c_str(), sizeof(head) - 1);
        char attribute[2] = "0";
        unsigned long nTriLong = skirt.size() + part.size();

        std::ofstream myfile;

        myfile.open((filename + "-out.stl").c_str(), ios::out | ios::binary);
        myfile.write(head, sizeof(head));
        myfile.write((char*)&nTriLong, 4);

        //write down every triangle
        for (auto it = skirt.begin(); it != skirt.end(); it++) {
            //normal vector coordinates
            write_point(myfile, it->N);
            write_point(myfile, it->point[0]);
            write_point(myfile, it->point[1]);
            write_point(myfile, it->point[2]);
            myfile.write(attribute, 2);
        }

        //write down every triangle
        for (auto it = part.begin(); it != part.end(); it++) {
            //normal vector coordinates
            write_point(myfile, it->N);
            write_point(myfile, it->point[0]);
            write_point(myfile, it->point[1]);
            write_point(myfile, it->point[2]);
            myfile.write(attribute, 2);
        }
        myfile.close();
    }

    static void write_point(ofstream& myfile, Point& P) {
        float x = P.x;            myfile.write((char*)&x, 4);
        float y = P.y;            myfile.write((char*)&y, 4);
        float z = P.z;            myfile.write((char*)&z, 4);
    }

};