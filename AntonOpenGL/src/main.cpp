#include <glew.h>
#include <glfw3.h>
#include "Shader.h"
#include <iostream>
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

int main() {

	Window window(800, 600, "OpenGL");
	window.Init();

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

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
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

	GLuint vao1, vao2, vertices_vbo, colors_vbo, ebo1, ebo2;
	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);
	GLCall(glGenBuffers(1, &vertices_vbo));
	GLCall(glGenBuffers(1, &colors_vbo));
	GLCall(glGenBuffers(1, &ebo1));
	GLCall(glGenBuffers(1, &ebo2));


	// bind VAO1 to bring it into focus in the statemachine
	GLCall(glBindVertexArray(vao1));
	
	/* a vertex buffer object (VBO) is created here. this stores an array of
	data on the graphics adapter's memory. in our case - the vertex points */
	//VertexBuffer vbo(vertices, 9);
	//vbo.Bind();
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, colors_vbo));
	//GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

	// Index Buffer Object
	//IndexBuffer ibo(indices, 6);
	//ibo.Bind();
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_one), tri_one, GL_STATIC_DRAW));

	 //Set up the VAO
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

	//GLCall(glEnableVertexAttribArray(1));
	//GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));

	// bind VAO2 to bring it into focus in the state machine
	GLCall(glBindVertexArray(vao2));

	// Index Buffer Object
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_two), tri_two, GL_STATIC_DRAW));

	// set up the VAO
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));



	Shader shader1("Shaders/Vertex.shader", "Shaders/Fragment.shader");
	Shader shader2("Shaders/Vertex.shader", "Shaders/Fragment2.shader");

	while (!window.Closed())
	{
		window.Clear(.5f, .5f, .5f);
		shader1.Use();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GLCall(glBindVertexArray(vao1));
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
		shader2.Use();
		GLCall(glBindVertexArray(vao2));
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
		window.Update();

	}
	return 0;
}
