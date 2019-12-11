#include "shader.h"

/**
 *  Creates a shader of a certain type from the source. 
 */ 
Shader::Shader(ShaderType type, const GLchar *pathToShader)
{
    this->type = type;
    readCompileShaderSource(pathToShader);
}

void Shader::readCompileShaderSource(const GLchar *pathToShader)
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
        std::cout << "ERROR: Could not read shader file\n" << std::endl;
    }

    const char* shaderCodePtr = shaderCode.c_str();

    shaderHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderHandle, 1, &shaderCodePtr, NULL);
    glCompileShader(shaderHandle);

    int success;
    char infoLog[512];
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);
        std::cout << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
    }
}

GLuint Shader::getHandle() { return shaderHandle; }

ShaderType Shader::getType() { return type; }