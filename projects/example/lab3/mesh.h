#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
};

#endif