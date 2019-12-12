#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "node.h"
#include <glm/glm.hpp>
#include <vector>

std::vector<glm::vec3> convexHull(std::vector<glm::vec3> points);
Node *buildTree(glm::vec3 c, std::vector<glm::vec3> vertices, Node *parent);
void triangleSoup(Node *tree);

#endif

