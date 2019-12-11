#include "shaderprogram.h"

ShaderProgram::ShaderProgram(Shaders shaders) 
{
    this->shaders = shaders;
    programID = glCreateProgram();
}

/** 
  * Inserts a shader resource pointer to the program.
 */
void ShaderProgram::addShaderResource(Shader* shader) 
{
    shaders.insert(shaders.end(), shader);
}

/**
 *  Attaches all shaders to the program and links them.
 */
void ShaderProgram::init() 
{
    for(int i = 0; i < shaders.size(); i++)
    {
        glAttachShader(programID, shaders[i]->getHandle());
    }

    int success;   
    char infoLog[512];
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "Error: Program linking failed." << infoLog << std::endl;
    }

}

void ShaderProgram::activate()
{
    glUseProgram(programID);
}