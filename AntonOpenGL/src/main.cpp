#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include <iostream>
#include "Window.h"

int main() {

	Window window(800, 600, "OpenGL");
	window.Init();
	log_gl_params();

	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	than anything already drawn at that pixel */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	/* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
	glDepthFunc(GL_LESS);

	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};

	unsigned int tri_one[] = {
	0, 1, 3
	};

	unsigned int tri_two[] = {
	1, 2, 3
	};

	GLuint vao1, vao2, vbo, ebo1, ebo2;
	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo1);
	glGenBuffers(1, &ebo2);

	// bind VAO1 to bring it into focus in the statemachine
	glBindVertexArray(vao1);
	
	/* a vertex buffer object (VBO) is created here. this stores an array of
	data on the graphics adapter's memory. in our case - the vertex points */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_one), tri_one, GL_STATIC_DRAW);

	// Set up the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// bind VAO2 to bring it into focus in the state machine
	glBindVertexArray(vao2);

	// Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_two), tri_two, GL_STATIC_DRAW);

	// set up the VAO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	Shader shader1("Shaders/Vertex.shader", "Shaders/Fragment.shader");
	Shader shader2("Shaders/Vertex.shader", "Shaders/Fragment2.shader");

	bool b = restart_gl_log();

	std::cout << "restart_gl_log() " << b << std::endl;

	while (!window.Closed())
	{
		window.Clear(.5f, .5f, .5f);
		shader1.Use();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao1);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		shader2.Use();
		glBindVertexArray(vao2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		window.Update();

	}
	return 0;
}
