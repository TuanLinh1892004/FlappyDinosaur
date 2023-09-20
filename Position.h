#pragma once

#include "ECS.h"
#include "SDL.h"

class Position : public Component
{
private:
    double x, y;
    double constx, consty;

public:
    Position(double posx, double posy)
    {
        constx = posx;
        consty = posy;
    }
    void init() override
    {
        x = constx;
        y = consty;
    }
    double getx() { return x; }
    double gety() { return y; }
    void setx(double posx) { x = posx; }
    void sety(double posy) { y = posy; }
    void up(double upx, double upy)
    {
        x += upx;
        y += upy;
    }
};
