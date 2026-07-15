#pragma once

#include <memory>
#include <unordered_map>

#include "object3D.hpp"

using ObjectIterator = std::unordered_map<std::string, std::unique_ptr<Object3D>>::const_iterator;

class Scene
{
public:
    Scene(std::string id);
    ~Scene();

    const std::string& getId() const;

    void addObject(std::unique_ptr<Object3D> obj);
    void removeObject(const std::string& objectId);

    Object3D* getObject(const std::string& objectId);

    ObjectIterator objectsStart() const;
    ObjectIterator objectsEnd() const;

    Mat4 getModelTransform(const std::string& objectId) const;
    Mat4 getCameraTransform() const;

    Vec4 getCameraPosition() const;
    Vec4 getLightSourcePosition() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> impl;

    friend class Playground;
};