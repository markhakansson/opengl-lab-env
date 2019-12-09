//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>

const GLchar *vs =
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) in vec3 pos;\n"
	"layout(location=1) in vec4 color;\n"
	"layout(location=0) out vec4 Color;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(pos, 1);\n"
	"	Color = color;\n"
	"}\n";

const GLchar *ps =
	"#version 310 es\n"
	"precision mediump float;\n"
	"layout(location=0) in vec4 color;\n"
	"out vec4 Color;\n"
	"void main()\n"
	"{\n"
	"	Color = vec4(1.0, 0.0, 0.0, 1.0);\n"
	"}\n";

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	this->filename = "input.txt";
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

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

		/* 		b->c = c;
		b->ci = vertices[0];
		b->cj = vertices[vertices.size() - 1];
		b->cm = vertices[median];
		b->left = left;
		b->right = right;
		b->parent = parent; */

		std::cout << "Returning bnode" << std::endl;
		return b;
	}
}

std::vector<glm::vec3> readInputFile(std::string filename)
{
	std::fstream file;
	std::vector<glm::vec3> vectors;
	std::string word, x, y;
	int noPoints = 0;

	file.open(filename);

	file >> word;
	noPoints = std::stoi(word);

	for (int i = 0; i < noPoints; i++)
	{
		file >> x;
		file >> y;

		glm::vec3 vec = glm::vec3(std::stof(x), std::stof(y), 0.0f);
		vectors.insert(vectors.end(), vec);
	}

	return vectors;
}

float generateFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	return min + random * diff;
}

std::vector<glm::vec3> generateRandomPoints(int noPoints)
{
	std::vector<glm::vec3> vertices;

	for (int i = 0; i < noPoints; i++)
	{
		float x = generateFloat(-1, 1);
		float y = generateFloat(-1, 1);

		std::cout << "X: " << x << " Y: " << y << std::endl;

		glm::vec3 vec = glm::vec3(x, y, 0.0f);
		vertices.insert(vertices.end(), vec);
	}

	std::cout << "# Points generated: " << vertices.size() << std::endl;

	return vertices;
}

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

void ExampleApp::calculateInnerPoints()
{
	if (this->points.size() > 0)
	{
		this->hull = convexHull(this->points);
		this->innerPoints = this->points;
		for (int i = 0; i < this->hull.size(); i++)
		{
			std::vector<glm::vec3>::iterator itr = std::find(this->innerPoints.begin(), this->innerPoints.end(), this->hull[i]);
			if (itr != this->innerPoints.end())
			{
				this->innerPoints.erase(itr);
			}
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
bool ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(1000, 1000);
	window->SetKeyPressFunction([this](int32 key, int32, int32 action, int32) {
		// 'input' read points from file
		if (key == GLFW_KEY_I && action == GLFW_PRESS)
		{
			this->points = readInputFile(this->filename);

			// 'random' generate random points
		}
		else if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			std::string line;
			std::getline(std::cin, line);
			int noPoints = std::stoi(line);
			this->points = generateRandomPoints(noPoints);
		}
		// triangulate
		else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		{
			calculateInnerPoints();

			glm::vec3 c = this->innerPoints[0];
			Node *tree = buildTree(c, this->hull, nullptr);
			//this->tree = tree;
		}
		else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			this->window->Close();
		}
		else if (key == GLFW_KEY_C && action == GLFW_PRESS)
		{
			this->hull = convexHull(this->points);
		}
		else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		{
			calculateInnerPoints();

			glm::vec3 basePoint = this->innerPoints[0];
			std::vector<glm::vec3> tmp;

			for (int i = 0; i < this->hull.size(); i++)
			{
				tmp.push_back(this->hull[i]);

				if (i == this->hull.size() - 1)
				{
					tmp.push_back(this->hull[0]);
				}
				else
				{
					tmp.push_back(this->hull[i + 1]);
				}

				tmp.push_back(basePoint);
			}
			this->edges = tmp;
		}
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = (GLint)std::strlen(vs);
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar *buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = (GLint)std::strlen(ps);
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar *buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar *buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		glGenBuffers(1, &this->buffer);
		glPointSize(8.0);

		return true;
	}

	return false;
}

//------------------------------------------------------------------------------
/**
*/
void ExampleApp::Run()
{
	this->points = {
		glm::vec3(-0.9f, 0.9f, 0.0f),
		glm::vec3(0.9f, 0.9f, 0.0f),
		glm::vec3(0.9f, -0.9f, 0.0f),
		glm::vec3(-0.9f, -0.9f, 0.0f),
		glm::vec3(-0.9f, 0.9f, 0.0f),
	};

	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		glUseProgram(this->program);
		glEnableVertexAttribArray(0);

		// points
		glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
		glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
		glDrawArrays(GL_POINTS, 0, points.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// hull
		if (hull.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glBufferData(GL_ARRAY_BUFFER, hull.size() * sizeof(glm::vec3), hull.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
			glDrawArrays(GL_LINE_LOOP, 0, hull.size());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (edges.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(glm::vec3), edges.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
			glDrawArrays(GL_LINE_LOOP, 0, edges.size());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		this->window->SwapBuffers();
	}
}

} // namespace Example