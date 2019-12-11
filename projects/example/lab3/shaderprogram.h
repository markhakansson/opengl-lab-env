#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include "shader.h"
#include "types.h"

class ShaderProgram
{
public:
    ShaderProgram(Shaders shaders);
    ~ShaderProgram();
    Shaders shaders;
    GLuint programID;
    void addShaderResource(Shader *shader);
    void init();
    void activate();
private:
};

#endif