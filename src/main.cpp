#include <cstdint>
#include <iostream>
#include <cmath>

#include "playground.hpp"

int main() 
{   
    PlayGround app;
    app.addObject("res/teapot.obj", {0, 0, 8});
    app.run();
}