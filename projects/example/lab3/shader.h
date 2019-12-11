#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum ShaderType
{
    FRAGMENT,
    VERTEX
};

class Shader
{
public:    
    Shader(ShaderType type, const GLchar *pathToShader);
    ~Shader();
    GLuint getHandle();
    ShaderType getType();

private:
    ShaderType type;
    GLuint shaderHandle; // handle to shaderprogram
    void readCompileShaderSource(const GLchar *pathToShader);
};

#endif