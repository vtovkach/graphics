#include <cstdint>
#include <iostream>
#include <cmath>

#include "playground.hpp"

int main() 
{   
    PlayGround app;
    app.addObject("res/VideoShip.obj", {0, 0, 10});
    app.run();
}