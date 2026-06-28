#pragma once

#include <vector>
#include "camera.hpp"
#include "lighting.hpp"
#include "object3D.hpp"

class Scene
{
public:
    std::vector<Object3D>& getObjects();
    Lighting& getLighting();
    Camera& getCamera();

private:
    std::vector<Object3D> objects; 
    Lighting light; 
    Camera camera;    
};