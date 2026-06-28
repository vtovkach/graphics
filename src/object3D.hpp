#pragma once 

#include <string>
#include "geometry.hpp"

class Object3D
{
public:
    explicit Object3D(const std::string& objPath);
    explicit Object3D(Mesh& mesh);

    void incObjPos(float dx, float dy, float dz);
    void setObjPos(float x, float y, float z);
    void changeObjSize(float x, float y, float z);
    void rotateObject(float thetaX, float thetaY, float thetaZ);

    Mesh getObjectMesh();
    Mat4 getModelTransform();

private:
    Mesh object; 
    Vec4 position; 
    Vec4 rotation; 
    Vec4 scale; 

    Mat4 modelTransform; 

    void updateModelTransform();
};