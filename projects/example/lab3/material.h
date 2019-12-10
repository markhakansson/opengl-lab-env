#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "shaderprogram.h"

class Material
{
public:
    Material();
    ~Material();
    ShaderProgram* shaderProgram;
    virtual void ApplyMaterial() = 0;

private:

};

#endif