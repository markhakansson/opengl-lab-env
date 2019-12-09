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
namespace Example
{
class ExampleApp : public Core::App
{
public:
	/// constructor
	ExampleApp();
	/// destructor
	~ExampleApp();

	/// open app
	bool Open();
	/// run app
	void Run();

	std::vector<glm::vec3> KochSnowflake(int depth, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
	
private:

	GLuint program;
	GLuint vertexShader;
	GLuint pixelShader;
	GLuint triangle;
	GLuint ibo;
	GLsizei no_of_points;

	int depth;
	std::vector<glm::vec3> vertices;
		
	Display::Window* window;
};
} // namespace Example