#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include "mesh.h"
#include "material.h"
#include <glm/mat4x4.hpp>

class GraphicsNode
{
public:
    Mesh* mesh;
    Material* material;
    glm::mat4 trasform;
    
    GraphicsNode();
    ~GraphicsNode();
    void Draw();
};

#endif