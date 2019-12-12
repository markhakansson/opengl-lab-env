#ifndef TOOLS_H
#define TOOLS_H

#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * 	If the points makes a clockwise turn the result will be negative.
 * 	If counter-clockwise the result is positive. If zero they are collinear.
 */
inline float cross(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
{
	return (p0.x - p2.x) * (p1.y - p2.y) - (p0.y - p2.y) * (p1.x - p2.x);
}

#endif