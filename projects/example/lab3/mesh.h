#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include "types.h"

class Mesh
{
public:
    Mesh(Vertices vertices);
    ~Mesh();
    
    Vertices vertices;
    Indices indices;

    /* VBO is basically an array of data buffers */
    GLuint vbo;
    GLuint ibo;
    GLuint vao;
};

#endif