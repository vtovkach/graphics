#pragma once

#include <unordered_map>
#include "scene.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "object3D.hpp"

class Scene::Impl
{
public:
    Impl(std::string sceneId)
    {
        this->sceneId = std::move(sceneId);
    } 

    std::string sceneId; 
    std::unordered_map<std::string, std::unique_ptr<Object3D>> objects;

    Lighting light;
    Camera camera;

    const Camera& getCamera() const;
    const Lighting& getLight() const; 
};

const Camera& Scene::Impl::getCamera() const
{
    return camera;
}

const Lighting&Scene::Impl::getLight() const
{
    return light;
}