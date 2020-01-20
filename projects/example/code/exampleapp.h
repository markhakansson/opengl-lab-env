#pragma once
//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015-2017 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/app.h"
#include <glm/glm.hpp>
#include "render/window.h"
#include <vector>
#include "node.h"

namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();
	void calculateInnerPoints();
	int prevKeyPress;

	/// open app
	bool Open();
	/// run app
	void Run();

private:
	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint buffer;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLsizei no_of_points;

	std::vector<GLfloat> vertexBuffer;

	std::vector<glm::vec3> points;
	std::vector<glm::vec3> hull;
	std::vector<glm::vec3> innerPoints;
	std::vector<glm::vec3> triangles;
	Node* tree;
	std::string filename;

	Display::Window* window;
};
} // namespace Example