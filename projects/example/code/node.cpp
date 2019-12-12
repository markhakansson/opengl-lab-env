#include "node.h"

std::vector<glm::vec3> BNode::getTriangles()
{
    std::vector<glm::vec3> triangles;

    std::vector<glm::vec3> leftTri = left->getTriangles();
    std::vector<glm::vec3> rightTri = right->getTriangles();

    triangles.insert(triangles.end(), leftTri.begin(), leftTri.end());
    triangles.insert(triangles.end(), rightTri.begin(), rightTri.end());

    return triangles;
}

std::vector<glm::vec3> Leaf::getTriangles()
{
    std::vector<glm::vec3> triangle;
    triangle.insert(triangle.end(), c);
    triangle.insert(triangle.end(), ci);
    triangle.insert(triangle.end(), ci1);
    return triangle;
}

std::vector<glm::vec3> TNode::getTriangles()
{
    std::vector<glm::vec3> triangles;

    std::vector<glm::vec3> leftTri = left->getTriangles();
    std::vector<glm::vec3> midTri = mid->getTriangles();
    std::vector<glm::vec3> rightTri = right->getTriangles();

    triangles.insert(triangles.end(), leftTri.begin(), leftTri.end());
    triangles.insert(triangles.end(), midTri.begin(), midTri.end());
    
    triangles.insert(triangles.end(), rightTri.begin(), rightTri.end());

    return triangles;
}