#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include "mesh.h"
#include "material.h"
#include <glm/mat4x4.hpp>
#include "types.h"

class GraphicsNode
{
public:
    Mesh *mesh;
    Material *material;
    mat4 transform;

    GraphicsNode(Mesh *mesh, Material *material, mat4 transform);
    void draw();
};

#endif