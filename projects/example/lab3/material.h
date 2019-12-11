#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "shaderprogram.h"

class Material
{
public:
    virtual void applyMaterial() = 0;
    ShaderProgram *shaderProgram;
};

#endif