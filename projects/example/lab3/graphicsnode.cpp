#include "graphicsnode.h"

GraphicsNode::GraphicsNode(Mesh *mesh, Material *material, mat4 transform)
{
    this->mesh = mesh;
    this->material = material;
    this->transform = transform;
}

void GraphicsNode::draw()
{
    // bind mesh object
    // call applymaterial of material
    // execute a drawcall

}