#include <cstdint>
#include <iostream>
#include <cmath>

#include "example.hpp"

int main() 
{   
    Example app("Renderer", 600, 1000);
    app.addObject("res/teapot.obj", Vec4(0, 0, 8, 0));
    app.run();
}