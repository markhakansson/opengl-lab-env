#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "shader.h"

typedef std::vector<glm::vec4> Vertices;
typedef std::vector<GLuint> Indices;
typedef std::vector<Shader*> Shaders;
typedef glm::vec4 vec4;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;
typedef glm::mat4 mat4;

struct Vertex {
    vec4 Position;
    vec3 Normal;
    vec2 UV;
};

#endif