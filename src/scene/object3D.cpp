#include "object3D.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

Object3D::Object3D(const std::string& objPath, const std::string& objectId)
{
    this->objectId = std::move(objectId);

    std::ifstream file(objPath);

    if(!file.is_open())
    {
        throw std::runtime_error(
            std::string("Failed to open a file \"") + objPath + "\""
        );
    }

    std::string line; 
    std::vector<Vec4> vertices;

    while(!file.eof())
    {
        std::getline(file, line);

        if(line.empty())
            continue;

        std::stringstream ss(line);

        char type; 
        ss >> type;
        if(type == 'v')
        {
            Vec4 v;
            v = {0, 0, 0, 1};
            ss >> v.x >> v.y >> v.z;
            vertices.push_back(v);
        }
        else if(type == 'f')
        {
            int idx[3];
            ss >> idx[0] >> idx[1] >> idx[2];
            object.triangles.push_back({vertices[idx[0] - 1], vertices[idx[1] - 1], vertices[idx[2] - 1]});
        }
    }

    position = {0, 0, 0, 1};
    rotation = {0, 0, 0, 1};
    scale = {1, 1, 1, 1};

    this->updateModelTransform();
}

Object3D::Object3D(Mesh& mesh, const std::string& objectId)
{
    this->objectId = std::move(objectId);
    
    object = mesh;
    position = {0, 0, 0, 1};
    rotation = {0, 0, 0, 1};
    scale = {1, 1, 1, 1};

    this->updateModelTransform();
}

void Object3D::setObjPos(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
    position.w = 1;

    this->updateModelTransform();
}

void Object3D::incObjPos(float dx, float dy, float dz)
{
    position.x += dx;
    position.y += dy;
    position.z += dz;

    this->updateModelTransform();
}

void Object3D::changeObjSize(float sx, float sy, float sz)
{
    scale.x += sx; 
    scale.y += sy;
    scale.z += sz;

    this->updateModelTransform();
}

void Object3D::rotateObject(float thetaX, float thetaY, float thetaZ)
{
    rotation.x += thetaX;
    rotation.y += thetaY;
    rotation.z += thetaZ;

    this->updateModelTransform();
}

// Used privately after any changes to the object's position 
void Object3D::updateModelTransform()
{
    Mat4 rotationTransformX = Transform::rotationXTransform(rotation.x);
    Mat4 rotationTransformY = Transform::rotationYTransform(rotation.y);
    Mat4 rotationTransformZ = Transform::rotationZTransform(rotation.z);
    Mat4 scaleTransform = Transform::scaleTransform(scale.x, scale.y, scale.z);
    Mat4 translateTransform = Transform::translateTransform(position.x, position.y, position.z);

    this->modelTransform = translateTransform * scaleTransform * rotationTransformX * rotationTransformY * rotationTransformZ;
}

Mesh Object3D::getObjectMesh() const
{
    return object;
}

Mat4 Object3D::getModelTransform() const
{
    return modelTransform;
}

const std::string& Object3D::getId() const
{
    return objectId;
}