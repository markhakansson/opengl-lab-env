#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "tools.h"
#include <iostream>

class Node
{
public:
	Node* parent; 

	Node(Node* parent) : parent(parent) {};
	virtual std::vector<glm::vec3> getTriangles() = 0;
	virtual Node *insert(glm::vec3 p) = 0;
};

class BNode : public Node
{
public:	
	Node* left;
	Node* right;
	glm::vec3 c, ci, cm, cj;

	//std::vector<glm::vec3> getTriangles();
	BNode(glm::vec3 c, glm::vec3 ci, glm::vec3 cm, glm::vec3 cj, Node* parent) :
		c(c), ci(ci), cm(cm), cj(cj), left(nullptr), right(nullptr), Node(parent) {};

	virtual std::vector<glm::vec3> getTriangles()
	{
		std::vector<glm::vec3> triangles;

		std::vector<glm::vec3> leftTri = left->getTriangles();
		std::vector<glm::vec3> rightTri = right->getTriangles();

		triangles.insert(triangles.end(), leftTri.begin(), leftTri.end());
		triangles.insert(triangles.end(), rightTri.begin(), rightTri.end());

		return triangles;
	}

	virtual Node *insert(glm::vec3 p) 
	{	
		// left of c->cm
		if(cross(c, cm, p) < 0)
		{
			Node *tmp = left->insert(p);
			if(tmp != nullptr) 
			{
				left = tmp;
			}
		}
		else if(cross(c, cm, p) > 0)
		{
			Node *tmp = right->insert(p);
			if(tmp != nullptr)
			{
				right = tmp;
			}
		}
		return nullptr;
	}
};

class TNode : public Node
{
public:	
	Node* left;
	Node* mid;
	Node* right;
	glm::vec3 c, ci, cm, cj;

	//std::vector<glm::vec3> getTriangles();
	TNode(glm::vec3 c, glm::vec3 ci, glm::vec3 cm, glm::vec3 cj, Node* parent) :
		c(c), ci(ci), cm(cm), cj(cj), Node(parent) {};
	virtual std::vector<glm::vec3> getTriangles()
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

	virtual Node *insert(glm::vec3 p) 
	{
		// left of c->ci 
		if(cross(c, ci, p) > 0)
		{	
			// left of c->cm
			if(cross(c, cm, p) > 0) 
			{	
				// right of c->cj
				if(cross(c, cj, p) < 0)
				{
					Node *tmp = mid->insert(p);
					if(tmp != nullptr)
					{
						mid = tmp;
					}
				}
			} 
			// right of c->cm
			else if(cross(c, cm, p) < 0) 
			{
				Node *tmp = left->insert(p);
				if(tmp != nullptr)
				{
					left = tmp;
				}				
			}
		} 
		// right of c->ci
		else if(cross(c, ci, p) < 0)	
		{	
			// right of c->cj
			if(cross(c, cj, p) < 0)
			{	
				// left of c->cm
				if(cross(c, cm, p) > 0)
				{
					Node *tmp = mid->insert(p);
					if(tmp != nullptr)
					{
						mid = tmp;
					}
				}
			} 
			// left of c->cj
			else if(cross(c, cj, p) > 0)
			{
				Node *tmp = right->insert(p);
				if(tmp != nullptr)
				{
					right = tmp;
				}
			}
		}

		return nullptr;

	}
};

class Leaf : public Node 
{
public:
	glm::vec3 c;
	glm::vec3 ci;
	glm::vec3 ci1;

	//std::vector<glm::vec3> getTriangles();
	Leaf(glm::vec3 c, glm::vec3 ci, glm::vec3 ci1, Node* parent) : 
		c(c), ci(ci), ci1(ci1), Node(parent) {};
	virtual std::vector<glm::vec3> getTriangles()
	{
		std::vector<glm::vec3> triangle;
		triangle.insert(triangle.end(), c);
		triangle.insert(triangle.end(), ci);
		triangle.insert(triangle.end(), ci1);
		return triangle;
	}

	virtual Node *insert(glm::vec3 p) 
	{	
		std::cout << "@@ Inside a leaf!" << std::endl;
		TNode *t = new TNode(p, c, ci, ci1, this->parent);
		Leaf *l1 = new Leaf(p, c, ci, t);
		Leaf *l2 = new Leaf(p, ci, ci1, t);
		Leaf *l3 = new Leaf(p, ci1, c, t);
		t->left = l1;
		t->mid = l2;
		t->right = l3;
		return t;
	}
};

#endif