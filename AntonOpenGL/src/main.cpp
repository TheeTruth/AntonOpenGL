#include <glew.h>
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
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CW); // GL_CCW for counter clock-wise


	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};

	float vert2[] = {
	-0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int tri_one[] = {
	0, 1, 2
	};

	unsigned int tri_two[] = {
	1, 2, 3
	};

	GLfloat matrix[] = {
	  1.0f, 0.0f, 0.0f, 0.0f, // first column 
	  0.0f, 1.0f, 0.0f, 0.0f, // second column 
	  0.0f, 0.0f, 1.0f, 0.0f, // third column 
	  0.5f, 0.0f, 0.0f, 1.0f // fourth column 
	};

	GLuint vao1, vao2, vertices_vbo, colors_vbo, ebo1, ebo2;
	glGenVertexArrays(1, &vao1);
	glGenBuffers(1, &vertices_vbo);
	//glGenVertexArrays(1, &vao2);

	// bind VAO1 to bring it into focus in the statemachine
	GLCall(glBindVertexArray(vao1));
	
	/* a vertex buffer object (VBO) is created here. this stores an array of
	data on the graphics adapter's memory. in our case - the vertex points */

	VertexBuffer vbo_points(vert2, sizeof(vert2));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));
	VertexBuffer vbo_colors(colors, sizeof(colors));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));
	
	IndexBuffer ibo(tri_one, 3);

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));



#pragma region triangle2

	//GLCall(glEnableVertexAttribArray(1));
	//GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL));

	// bind VAO2 to bring it into focus in the state machine
	//GLCall(glBindVertexArray(vao2));

	// Index Buffer Object
	//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2));
	//GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tri_two), tri_two, GL_STATIC_DRAW));

	// set up the VAO
	//GLCall(glEnableVertexAttribArray(0));
	//GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL));

#pragma endregion triangle2


	Shader shader1("Shaders/Vertex.shader", "Shaders/Fragment.shader");
	//Shader shader2("Shaders/Vertex.shader", "Shaders/Fragment2.shader");

	int model_matrix_location = glGetUniformLocation(shader1.ID, "model_matrix");
	shader1.Use();
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, matrix);

	while (!window.Closed())
	{
		window.Clear(.5f, .5f, .5f);
		shader1.Use();
		GLCall(glBindVertexArray(vao1));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
		//shader2.Use();
		//GLCall(glBindVertexArray(vao2));
		//GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
		window.Update();

	}
	return 0;
}
