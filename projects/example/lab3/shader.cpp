#include "shader.h"

Shader::Shader(ShaderType type, const GLchar *pathToShader)
{
    this->type = type;
    readShaderSource(pathToShader);
}

void readShaderSource(const GLchar *pathToShader)
{
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(pathToShader);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR: Could not read shader file" << std::endl;
    }
}

void compileShader() {}

GLuint Shader::getHandle() { return shaderHandle; }

ShaderType Shader::getType() { return type; }