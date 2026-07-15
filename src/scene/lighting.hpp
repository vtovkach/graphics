#pragma once 

#include "v-math.hpp"

class Lighting
{
public:
    Vec4 lightSourcePos = {0, 0, -1.0f, 0};

    Vec4 getPosition() const;
};