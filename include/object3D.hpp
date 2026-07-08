#pragma once 

#include <string>
#include <vector>
#include "v-math.hpp"

struct Mesh
{
    std::vector<Triangle> triangles; 
};

class Object3D
{
public:
    explicit Object3D(const std::string& objPath, const std::string& objectId);
    explicit Object3D(Mesh& mesh, const std::string& objectId);

    void incObjPos(float dx, float dy, float dz);
    void setObjPos(float x, float y, float z);
    void changeObjSize(float x, float y, float z);
    void rotateObject(float thetaX, float thetaY, float thetaZ);

    Mesh getObjectMesh() const;
    Mat4 getModelTransform() const;

    const std::string& getId() const;

private:
    std::string objectId;

    Mesh object; 
    Vec4 position; 
    Vec4 rotation; 
    Vec4 scale; 

    Mat4 modelTransform; 

    void updateModelTransform();
};