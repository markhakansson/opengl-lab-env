#ifndef MONOCHROMEMATERIAL_H
#define MONOCHROMEMATERIAL_H

#include "material.h"
#include "types.h"

class MonochromeMaterial : public Material
{
public: 
    MonochromeMaterial(vec3 color);
    virtual void applyMaterial();
    
    vec3 color;
};

#endif