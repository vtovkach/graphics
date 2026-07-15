#include <stdexcept>

#include "sceneIMPL.hpp"

Scene::Scene(std::string sceneId) : impl(std::make_unique<Impl>(sceneId)) {};

Scene::~Scene() = default;

ObjectIterator Scene::objectsStart() const
{
    return impl->objects.cbegin();
}

ObjectIterator Scene::objectsEnd() const
{
    return impl->objects.cend();
}

const std::string& Scene::getId() const
{
    return impl->sceneId;
}

void Scene::addObject(std::unique_ptr<Object3D> obj)
{
    std::string id = obj->getId();

    if(impl->objects.find(id) != impl->objects.end())
    {
        throw std::runtime_error("Object already exists: " + id);
    }

    impl->objects.emplace(id, std::move(obj));
}

void Scene::removeObject(const std::string& objectId)
{
    if(impl->objects.find(objectId) == impl->objects.end())
    {
        throw std::runtime_error("Object does not exist: " + objectId);
    }

    impl->objects.erase(objectId);
}   

Object3D* Scene::getObject(const std::string& objectId)
{
    auto it = impl->objects.find(objectId);

    if (it == impl->objects.end()) 
    {
        return nullptr;
    }
    
    return it->second.get();
}

Mat4 Scene::getModelTransform(const std::string& objectId) const
{
    auto it = impl->objects.find(objectId);

    if(it == impl->objects.end())
    {
        std::runtime_error(
            "Failed to retrieve model transformation for the following object: " + 
            objectId
        );
    }

    Object3D *obj = it->second.get();
    return obj->getModelTransform();
}

Mat4 Scene::getCameraTransform() const
{
    return impl->getCamera().getCameraTransform();
}

Vec4 Scene::getCameraPosition() const
{
    return impl->camera.getPosition();
}

Vec4 Scene::getLightSourcePosition() const
{
    return impl->light.getPosition();
}