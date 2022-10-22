// MachinaLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "../Header/Header.h"
#include "../Header/Geometry/Wireframe.h"
#include "../Header/Topology/Topology.h"
#include "../Header/Geometry/Tessellation.h"
#include "../Header/IO/Parameters.h"

using namespace std;

void getInput() {
    Parameters();
    int type;
    cout << "Enter Input File Option number?\n\t1   ->   Part.STL\n\t2   ->   Part.txt\n" << endl;
    cin >> type;
    //type = 1;
    Parameters::file = "./Parts/Part";
    if (type == 1) Parameters::type = "STL";
    if (type == 2) Parameters::type = "txt";

    cout << "---------------------------------------------" << endl;

}
void displayParams() {
    
    cout << "Parameters values are..." << endl << endl;
    Parameters::file += "." + Parameters::type;
    cout << "\tFile \t\t:\t" << Parameters::file << endl;
    cout << "\tTolerence \t:\t" << Parameters::tolerence << endl;
    cout << "\tStep \t\t:\t" << Parameters::step << endl;
    cout << "\tslope \t\t:\t" << Parameters::slope << endl;
    cout << "\tMin Angle \t:\t" << Parameters::min_angle << endl;
    cout << "\tSprawl \t\t:\t" << Parameters::sprawl << endl;

}


int main()
{
    getInput();
    displayParams();
    Topology part(Parameters::file, Parameters::type);
    Wireframe frame(part);
    Skirt skirt(frame, part.nodes, part.mesh);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
