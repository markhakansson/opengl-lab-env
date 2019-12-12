#include "triangulation.h"
#include <vector>
#include <iostream>
#include <algorithm>

/**
 * 	If the points makes a clockwise turn the result will be negative.
 * 	If counter-clockwise the result is positive. If zero they are collinear.
 */
float crossProduct(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2)
{
	return (p0.x - p2.x) * (p1.y - p2.y) - (p0.y - p2.y) * (p1.x - p2.x);
}

void sortPoints(std::vector<glm::vec3> &points)
{
	std::sort(points.begin(), points.end(),
			  [](const glm::vec3 &first, const glm::vec3 &second) {
				  if (first.x == second.x)
				  {
					  return first.y < second.y;
				  }
				  else
				  {
					  return first.x < second.x;
				  }
			  });
}

/**
 *  Calculates the convext hull with Andrew's algorithm.
 */
std::vector<glm::vec3> convexHull(std::vector<glm::vec3> points)
{

	if (points.size() <= 3)
	{
		return points;
	}

	std::vector<glm::vec3> upperHull;
	std::vector<glm::vec3> lowerHull;

	sortPoints(points);

	// Calculate lower hull
	for (int i = 0; i < points.size(); ++i)
	{
		while (lowerHull.size() >= 2 && crossProduct(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], points[i]) <= 0)
		{
			lowerHull.pop_back();
		}
		lowerHull.push_back(points[i]);
	}

	// Calculate upper hull
	for (int i = points.size() - 1; i >= 0; --i)
	{
		while (upperHull.size() >= 2 && crossProduct(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], points[i]) <= 0)
		{
			upperHull.pop_back();
		}
		upperHull.push_back(points[i]);
	}

	// Remove last points and concatenate the upper and lower hull
	lowerHull.pop_back();
	upperHull.pop_back();

	lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

	std::cout << "Convex hull size: " << lowerHull.size() << std::endl;

	//for(int i = 0; i < lowerHull.size(); i++) {
	//	std::cout << "X: " << lowerHull[i].x << " Y: " << lowerHull[i].y << std::endl;
	//}

	return lowerHull;
}

/**
 * 	Builds a 2-3 tree from scratch.
 */
Node *buildTree(glm::vec3 c, std::vector<glm::vec3> vertices, Node *parent)
{
	std::cout << "Vertices size: " << vertices.size() << std::endl;
	if (vertices.size() == 2)
	{
		std::cout << "Returning leaf" << std::endl;
		return new Leaf(c, vertices[0], vertices[1], parent);
	}
	else
	{
		int median = vertices.size() / 2;
		BNode *b = new BNode(c, vertices[0], vertices[median], vertices[vertices.size() - 1], parent);

		std::cout << "Vertices median: " << median << std::endl;

		std::cout << "# Building left subtree!" << std::endl;
		b->left = buildTree(c, std::vector<glm::vec3>(vertices.begin(), vertices.begin() + median + 1), b);
		std::cout << "# Finished building left subtree!" << std::endl;
		std::cout << "* Building right subtree!" << std::endl;
		b->right = buildTree(c, std::vector<glm::vec3>(vertices.begin() + median, vertices.end()), b);
		std::cout << "* Finished building right subtree!" << std::endl;

		std::cout << "Returning bnode" << std::endl;
		return b;
	}
}

void triangleSoup(Node *tree)
{
}
