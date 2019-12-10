#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include "shader.h"

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    Shader* shader;
    GLuint program;
};

#endif