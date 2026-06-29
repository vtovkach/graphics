#include "scene.hpp"

std::vector<Object3D>& Scene::getObjects()
{
    return objects;
}

Lighting& Scene::getLighting()
{
    return light;
}

Camera& Scene::getCamera()
{
    return camera;
}

void Scene::addObject(Object3D obj)
{
    objects.push_back(obj);
}