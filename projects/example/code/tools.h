#ifndef TOOLS_H
#define TOOLS_H

#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * 	If the points makes a clockwise turn the result will be negative.
 * 	If counter-clockwise the result is positive. If zero they are collinear.
 */
inline float cross(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &p2)
{
	return (p0.x - p2.x) * (p1.y - p2.y) - (p0.y - p2.y) * (p1.x - p2.x);
}

/**
 *  Check if point p is within the sector bounded by c, ci and cm.
 */
inline bool pointInSector(glm::vec3 c, glm::vec3 ci, glm::vec3 cm, glm::vec3 p)
{
	if (cross(c, cm, p) < 0 && cross(c, ci, p) > 0)
	{
		return true;
	}
	else if (cross(c, cm, p) > 0 && cross(c, ci, p) < 0)
	{
		return true;
	}
	else if (cross(c, cm, p) < 0 && cross(c, ci, p) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif