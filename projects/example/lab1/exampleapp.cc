//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2017 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
#include <glm/glm.hpp>
#include <cmath>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>

const GLchar* vs =
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

const GLchar* ps =
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
	this->depth = 1;
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	this->window->SetSize(1000, 1000);
	window->SetKeyPressFunction([this](int32 key, int32, int32, int32)
	{
		if (key >= GLFW_KEY_1 || key <= GLFW_KEY_9) 
		{
			this->depth = key - 48;
		} 

		else if(key == GLFW_KEY_ESCAPE)
		{
			this->window->Close();
		}
		
		std::cout << this->depth << std::endl;

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
			GLchar* buf = new GLchar[shaderLogSize];
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
			GLchar* buf = new GLchar[shaderLogSize];
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
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		return true;
	}

	return false;

}

/**
 * Calculates the midpoint on the vector between point1 and point2. 
 */
glm::vec3 
calcMidpoint(glm::vec3 point0, glm::vec3 point1) 
{
	return 0.5f*(point0 + point1);
}

glm::vec3
normalizeVector(glm::vec3 point0, glm::vec3 point1) 
{
	return glm::normalize(point1 - point0);
}

float
magnitudeVector(glm::vec3 point0, glm::vec3 point1) 
{
	return glm::length(point1 - point0);
}

/**
 *  Returns a triangle with the points q0, a and q1 in that order.
 */
std::vector<glm::vec3>
createTriangle(glm::vec3 p0, glm::vec3 p1, glm::vec3 b) 
{
	float q0_x = (2.0f * p0.x + p1.x)/3.0f;
	float q0_y = (2.0f * p0.y + p1.y)/3.0f;
	float q1_x = (p0.x + 2.0f * p1.x)/3.0f;
	float q1_y = (p0.y + 2.0f * p1.y)/3.0f;
	glm::vec3 q0 = glm::vec3(q0_x, q0_y, 0);
	glm::vec3 q1 = glm::vec3(q1_x, q1_y, 0);	
	glm::vec3 m = 0.5f * (p0 + p1);

	// Univ vector of the vector b->m
	glm::vec3 uv = glm::normalize(m - b);

	// Determine point 'a'
	float p0p1_len = magnitudeVector(p0, p1);
	float hypo = p0p1_len/3.0f;
	float a_height = sqrtf(powf(hypo, 2.0f) - powf(0.5 * hypo, 2.0f));
	glm::vec3 a = m + uv * a_height;

	std::vector<glm::vec3> triangle;
	triangle.insert(triangle.end(), q0);
	triangle.insert(triangle.end(), a);
	triangle.insert(triangle.end(), q1);
	
	return triangle;

} 

// Helper function for recursively creating a snowflake
std::vector<glm::vec3>
buildSnowflake(int depth, glm::vec3 p0, glm::vec3 p1, glm::vec3 b) 
{
	std::vector<glm::vec3> result;

	// Return the edge as is
	if (depth == 1) {
		result.insert(result.end(), p0);
		result.insert(result.end(), p1);

	} else {
		// Calculate the new triangle for this edge
		std::vector<glm::vec3> triangle = createTriangle(p0, p1, b);
		glm::vec3 q0 = triangle[0];
		glm::vec3 a = triangle[1];
		glm::vec3 q1 = triangle[2];

		// Calculate the q0 on the next edge and q1 on the previous edge
		std::vector<glm::vec3> temp0 = createTriangle(p1, b, p0);
		std::vector<glm::vec3> temp1 = createTriangle(b, p0, p1);
		glm::vec3 q0_fw = temp0[0];
		glm::vec3 q1_bw = temp1[2];
	
		// Recursively build the edges (4 new edges for each edge)
		std::vector<glm::vec3> p0_q0 = buildSnowflake(depth - 1, p0, q0, q1_bw);
		std::vector<glm::vec3> q0_a = buildSnowflake(depth - 1, q0, a, q1);
		std::vector<glm::vec3> a_q1 = buildSnowflake(depth -1 , a, q1, q0);
		std::vector<glm::vec3> q1_p1 = buildSnowflake(depth - 1, q1, p1, q0_fw);

		result.insert(result.end(), p0_q0.begin(), p0_q0.end());
		result.insert(result.end(), q0_a.begin(), q0_a.end());
		result.insert(result.end(), a_q1.begin(), a_q1.end());
		result.insert(result.end(), q1_p1.begin(), q1_p1.end());	

	}

	return result;

}

/**
 *  Creates a Koch snowflake.
 */
std::vector<glm::vec3>
ExampleApp::KochSnowflake(int depth, glm::vec3 p0, glm::vec3 p1, glm::vec3 b) 
{	
	// Build the three sides of the triangle
	std::vector<glm::vec3> p0_p1 = buildSnowflake(depth, p0, p1, b);
	std::vector<glm::vec3> p1_b = buildSnowflake(depth, p1, b, p0);
	std::vector<glm::vec3> b_p0 = buildSnowflake(depth, b, p0, p1);

	std::vector<glm::vec3> res;
	res.insert(res.end(), p0_p1.begin(), p0_p1.end());
	res.insert(res.end(), p1_b.begin(), p1_b.end());
	res.insert(res.end(), b_p0.begin(), b_p0.end());

	return res;

}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{	
	// Initial vertices
	std::vector<glm::vec3> initVertices = {
		0.75f * glm::vec3(-0.866f, -0.5f, 0.0f),
		0.75f * glm::vec3(0.0f, 1.0f, 0.0f),
		0.75f * glm::vec3(0.866f, -0.5f, 0.0f),
	};
	
	while (this->window->IsOpen())
	{
		this->vertices = KochSnowflake(this->depth, initVertices[0],initVertices[1], initVertices[2]);
		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		this->window->Update();

		// do stuff
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glUseProgram(this->program);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // point
		glLineWidth(2);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		this->window->SwapBuffers();
	}
}

} // namespace Example