#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

typedef std::vector<glm::vec4> Vertices;
typedef std::vector<GLuint> Indices;
typedef glm::vec4 Vec4;
typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;

struct Vertex {
    Vec4 Position;
    Vec3 Normal;
    Vec2 UV;
};

#endif