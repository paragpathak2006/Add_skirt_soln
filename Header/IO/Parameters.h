#pragma once
#include <string>
using namespace std;
class Parameters
{
public:
    static double slope;        static string file;
    static double sprawl;       static string type;
    static double min_angle;    static int step;
    static double tolerence;

    Parameters() {
        step = 10;
        slope = 4;
        min_angle = 10;
        sprawl = 4;
        tolerence = 1e-5;
        type = "STL";
        file = "./Parts/Part." + type;
    }


};



