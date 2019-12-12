#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "tools.h"

class Node
{
public:
	Node* parent; 

	Node(Node* parent) : parent(parent) {};
	virtual std::vector<glm::vec3> getTriangles() = 0;
	virtual Node *insert(glm::vec3 p);
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

	std::vector<glm::vec3> getTriangles()
	{
		std::vector<glm::vec3> triangles;

		std::vector<glm::vec3> leftTri = left->getTriangles();
		std::vector<glm::vec3> rightTri = right->getTriangles();

		triangles.insert(triangles.end(), leftTri.begin(), leftTri.end());
		triangles.insert(triangles.end(), rightTri.begin(), rightTri.end());

		return triangles;
	}

	Node *insert(glm::vec3 p) 
	{	
		Node* ptr = nullptr;
		// left of c->cm
		if(crossp(c, cm, p) > 0)
		{
			Node *tmp = left->insert(p);
			if(tmp != nullptr) 
			{
				ptr = tmp;
			}
		}
		else if(crossp(c, cm, p) < 0)
		{
			Node *tmp = right->insert(p);
			if(tmp != nullptr)
			{
				ptr = tmp;
			}
		}
		return ptr;
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
	std::vector<glm::vec3> getTriangles()
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

	Node *insert(glm::vec3 p) 
	{
		Node *ptr = nullptr;
		// left of c->ci 
		if(crossp(c, ci, p) > 0)
		{	
			// left of c->cm
			if(crossp(c, cm, p) > 0) 
			{	
				// right of c->cj
				if(crossp(c, cj, p) < 0)
				{
					Node *tmp = mid->insert(p);
					if(tmp != nullptr)
					{
						ptr = tmp;
					}
				}
			} 
			// right of c->cm
			else if(crossp(c, cm, p) < 0) 
			{
				Node *tmp = left->insert(p);
				if(tmp != nullptr)
				{
					ptr = tmp;
				}				
			}
		} 
		// right of c->ci
		else if(crossp(c, ci, p) < 0)	
		{	
			// right of c->cj
			if(crossp(c, cj, p) < 0)
			{	
				// left of c->cm
				if(crossp(c, cm, p) > 0)
				{
					Node *tmp = mid->insert(p);
					if(tmp != nullptr)
					{
						ptr = tmp;
					}
				}
			} 
			// left of c->cj
			else if(crossp(c, cj, p) > 0)
			{
				Node *tmp = right->insert(p);
				if(tmp != nullptr)
				{
					ptr = tmp;
				}
			}
		}

		return ptr;

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
	std::vector<glm::vec3> getTriangles()
	{
		std::vector<glm::vec3> triangle;
		triangle.insert(triangle.end(), c);
		triangle.insert(triangle.end(), ci);
		triangle.insert(triangle.end(), ci1);
		return triangle;
	}

	Node *insert(glm::vec3 p) 
	{	
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