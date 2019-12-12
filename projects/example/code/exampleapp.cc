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
//#include "triangulation.h"

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
	
	lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());

	return lowerHull;
}

/**
 * 	Builds a 2-3 tree from scratch.
 */
Node *buildTree(glm::vec3 c, std::vector<glm::vec3> vertices, Node *parent)
{
	if (vertices.size() == 2)
	{
		std::cout << "--------LEAF-------" << std::endl;
		std::cout << "c: " << "(" << c.x << ", " << c.y << ")" << std::endl;
		std::cout << "ci: " << "(" << vertices[0].x << ", " << vertices[0].y << ")" << std::endl;
		std::cout << "cj: " << "(" << vertices[1].x << ", " << vertices[1].y << ")" << std::endl;

		return new Leaf(c, vertices[0], vertices[1], parent);
	}
	else
	{
		int median = vertices.size() / 2;
		BNode *b = new BNode(c, vertices[0], vertices[median], vertices[vertices.size() - 1], parent);

		b->left = buildTree(c, std::vector<glm::vec3>(vertices.begin(), vertices.begin() + median + 1), b);
		b->right = buildTree(c, std::vector<glm::vec3>(vertices.begin() + median, vertices.end()), b);

		std::cout << "# Returning bnode" << std::endl;
		return b;
	}
}

void triangleSoup(Node *tree)
{
}

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

void ExampleApp::calculateInnerPoints()
{
	if (this->points.size() > 0)
	{
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
			this->hull = convexHull(this->points);

		// 'random' generate random points
		}
		else if (key == GLFW_KEY_R && action == GLFW_PRESS)
		{
			std::string line;
			std::getline(std::cin, line);
			int noPoints = std::stoi(line);
			this->points = generateRandomPoints(noPoints);
			this->hull = convexHull(this->points);
		}
		// triangulate
		else if (key == GLFW_KEY_T && action == GLFW_PRESS)
		{
			calculateInnerPoints();

			if(innerPoints.size() > 0) 
			{
				glm::vec3 c = this->innerPoints[0];
				tree = buildTree(c, this->hull, nullptr);

				for(int i = 1; i < innerPoints.size(); i++)
				{
					tree->insert(innerPoints[i]);
				}

				this->triangles = tree->getTriangles();
				std::cout << triangles.size() << std::endl;
			}
		} 
		else if (key == GLFW_KEY_P && action == GLFW_PRESS)
		{

		}		
		else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			this->window->Close();
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

		// draw points
		glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
		glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
		glDrawArrays(GL_POINTS, 0, points.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

 		// draw hull
/* 		if (hull.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glBufferData(GL_ARRAY_BUFFER, hull.size() * sizeof(glm::vec3), hull.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
			glDrawArrays(GL_LINE_LOOP, 0, hull.size());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		} 
 */
		// draw triangulation
		if (triangles.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(glm::vec3), triangles.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
			glDrawArrays(GL_LINE_STRIP, 0, triangles.size());
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		this->window->SwapBuffers();
	}
}

} // namespace Example