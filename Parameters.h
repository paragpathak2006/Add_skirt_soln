#pragma once
class Parameters
{
public:
    int step = 10;
    double slope = 2;
    double sprawl= 4;
    double min_angle = 10;
    Parameters() { step = 10;slope = 2; min_angle = 10; sprawl = 4; }
    Parameters(int step_in, double slope_in, double min_angle_in, double sprawl_in)
    {
        step = step_in;
        slope = slope_in;
        min_angle = min_angle_in;
        sprawl = sprawl_in;
    }

};

