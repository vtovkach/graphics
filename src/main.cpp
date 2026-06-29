#include <cstdint>
#include <iostream>
#include <cmath>

#include "playground.hpp"

int main() 
{   
    PlayGround app;
    app.addObject("res/VideoShip.obj", {1, 1, 3});
    app.run();
}