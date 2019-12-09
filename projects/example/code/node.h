#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>

struct Node
{
	Node* parent; 

	Node(Node* parent) : parent(parent) {};
	virtual void insert(glm::vec3 point);
};

struct BNode : public Node
{
	Node* left;
	Node* right;
	glm::vec3 c, ci, cm, cj;

	BNode(glm::vec3 c, glm::vec3 ci, glm::vec3 cm, glm::vec3 cj, Node* parent) :
		c(c), ci(ci), cm(cm), cj(cj), left(nullptr), right(nullptr), Node(parent) {};
};

struct Leaf : public Node 
{
	glm::vec3 c;
	glm::vec3 ci;
	glm::vec3 ci1;

	Leaf(glm::vec3 c, glm::vec3 ci, glm::vec3 ci1, Node* parent) : 
		c(c), ci(ci), ci1(ci1), Node(parent) {};

};

struct TNode : public Node
{
	Node* left;
	Node* mid;
	Node* right;
	glm::vec3 c, ci, cm, cj;

	TNode(glm::vec3 c, glm::vec3 ci, glm::vec3 cm, glm::vec3 cj, Node* parent) :
		c(c), ci(ci), cm(cm), cj(cj), Node(parent) {};
};

#endif