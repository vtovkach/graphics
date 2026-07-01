#include <cstdint>
#include <iostream>
#include <cmath>

#include "playground.hpp"

int main() 
{   
    PlayGround app;
    app.addObject("res/teapot.obj", Vec4(0, 0, 8, 0));
    app.run();
}