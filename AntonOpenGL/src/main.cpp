#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "benny/transform.h"



#define WIDTH 1280
#define HEIGHT 720

double deltaTime = 0;
double lastTime = 0;
Camera camera;
bool Camera::lock_camera = false;

int main() {

	Window window(WIDTH, HEIGHT, "OpenGL");
	window.Init();

	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();

	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	than anything already drawn at that pixel */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	/* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
	glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE); // cull face
	//glCullFace(GL_BACK); // cull back face
	//glFrontFace(GL_CW); // GL_CCW for counter clock-wise



	float vertices[] = {
		//positions			 texture coords 
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,	// top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,	// bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,	// bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,	// top left 
											//
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f,	// back top right
		 0.5f, -0.5f, 1.0f,  1.0f, 0.0f,	// back bottom right
		-0.5f, -0.5f, 1.0f,  0.0f, 0.0f,	// back bottom left
		-0.5f,  0.5f, 1.0f,  0.0f, 1.0f		// back top left
	};

	float normals[] = {
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f,
		0.f, 0.f, -1.f
	};

	float vertices2[] = {
		//positions			 texture coords		normals
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.f,	0.f, -1.f,// top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.f,	0.f, -1.f,// bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 0.f,	0.f, -1.f,// bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.f, 	0.f, -1.f, // top left 

		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 0.f, 	0.f, -1.f,// back top right
		 0.5f, -0.5f, 1.0f,  1.0f, 0.0f, 0.f, 	0.f, -1.f,// back bottom right
		-0.5f, -0.5f, 1.0f,  0.0f, 0.0f, 0.f, 	0.f, -1.f,// back bottom left
		-0.5f,  0.5f, 1.0f,  0.0f, 1.0f, 0.f, 	0.f, -1.f // back top left
	};

	unsigned int indices[] = {
		0, 1, 3, // front face
		1, 2, 3, // front face

		4, 5, 7, // back face
		5, 6, 7 // back face
	};

	unsigned int size = sizeof(indices) / sizeof(indices[0]);
	Vertex cube_vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
	};

	unsigned int cube_indices[] = { 0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	};

	//gets the array size
	unsigned int indices_size = sizeof(cube_indices) / sizeof(cube_indices[0]);
	unsigned int vertices_size = sizeof(cube_vertices) / sizeof(cube_vertices[0]);

	Mesh mesh(cube_vertices, vertices_size, cube_indices, indices_size);
	// projection matrix: ortho - 4:3 aspect ratio
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -.75f, .75f, -1.0f, 1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(65.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
	camera = Camera(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -10.0f, 15.0f, 5.0f, 0.1f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
;
	model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
	model = glm::rotate(model, glm::radians(90.0f), yAxis);
	Transform transform;
	//Camera camera();
	glm::mat4 view = glm::mat4(1.0f);
	view = camera.CalculateViewMatrix();

	//transform.SetPos();

	GLuint vao1, vao2;
	glGenVertexArrays(1, &vao1);
	glGenVertexArrays(1, &vao2);


	#pragma region triangle2

	GLCall(glBindVertexArray(vao2));

	// Position attribute
	VertexBuffer vbo_points2(vertices2, sizeof(vertices2));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	// texture coord attribute
	VertexBuffer vbo_texture(vertices2, sizeof(vertices2));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(1));

	VertexBuffer vbo_normals(vertices2, sizeof(vertices2));
	GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))));
	GLCall(glEnableVertexAttribArray(2));

	IndexBuffer indexBuffer(indices, size);

#pragma endregion triangle2

	// Texture
	Texture texture("Res/wall.jpg");

	Shader shader1("Shaders/Vertex.shader", "Shaders/Fragment.shader");
	Shader shader2("Shaders/Vertex2.shader", "Shaders/Fragment2.shader");
	Shader texShader("Shaders/VertTexture.shader", "Shaders/FragTexture.shader");

	glm::mat4 mvp = projection * view * model;

	int model_matrix_location = glGetUniformLocation(shader1.ID, "u_MVP");

	float start_time = glfwGetTime();
	

	while (!window.Closed())
	{
		double now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		//float xRot = sinf(now);
		float zRot = cosf(now);

		camera.KeyControl(window.getsKeys(), deltaTime);


		camera.MouseControl(window.getXChange(), window.getYChange());

		projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth()/ (float)window.GetHeight(), 0.1f, 100.0f);
		view = camera.CalculateViewMatrix();

		auto scale_value = glm::vec3(window.GetScaleSliderValue());
		transform.SetScale(scale_value);

		//auto rotation_value = window.GetRotationSliderValue();
		//transform.SetRot(rotation_value);


		auto translation_value = window.GetTranslationSliderValue();
		transform.SetPos(translation_value);


		model = transform.GetModel();
		mvp = projection * view * model;

		texShader.Use();
		GLCall(glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(mvp)));

		window.Clear(.5f, .5f, .5f);
		texShader.Use();
		GLCall(glBindVertexArray(vao2));
		GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));
		window.Update();

	}
	return 0;
}








