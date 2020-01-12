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
#include "benny/mesh.h"
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

	float vertices2[] = {
		//positions			 texture coords		normals
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,	0.0f, 0.0f, -1.f,// top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,	0.0f, 0.0f, -1.f,// bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,	0.0f, 0.0f, -1.f,// bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,	0.0f, 0.0f, -1.f, // top left 
											  		
		 0.5f,  0.5f, 1.0f,  1.0f, 1.0f,	0.0f, 0.0f, -1.f,// back top right
		 0.5f, -0.5f, 1.0f,  1.0f, 0.0f,	0.0f, 0.0f, -1.f,// back bottom right
		-0.5f, -0.5f, 1.0f,  0.0f, 0.0f,	0.0f, 0.0f, -1.f,// back bottom left
		-0.5f,  0.5f, 1.0f,  0.0f, 1.0f,	0.0f, 0.0f, -1.f // back top left
	};


	unsigned int indices[] = {
		0, 1, 3, // front face
		1, 2, 3, // front face

		4, 5, 7, // back face
		5, 6, 7 // back face
	};

	// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
	float light_vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
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
	camera = Camera(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -30.0f, 10.0f, 5.0f, 0.1f);

	glm::mat4 objectModel = glm::mat4(1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	glm::vec3 xAxis(1.0f, 0.0f, 0.0f);
	glm::vec3 yAxis(0.0f, 1.0f, 0.0f);
	glm::vec3 zAxis(0.0f, 0.0f, 1.0f);

	Transform objectTransform;
	Transform lightTransform;
	glm::mat4 view = glm::mat4(1.0f);
	//view = camera.CalculateViewMatrix();

	//transform.SetPos();

		GLuint light_vao, object_vao;
		GLCall(glGenVertexArrays(1, &light_vao));
		GLCall(glGenVertexArrays(1, &object_vao));

#pragma region light

		GLCall(glBindVertexArray(light_vao));
		VertexBuffer light_vbo(light_vertices, sizeof(light_vertices));
		//light_vbo.Bind();
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
		GLCall(glEnableVertexAttribArray(0));

#pragma endregion light


#pragma region object

		GLCall(glBindVertexArray(object_vao));
		std::cout << "sizeof(vertices2) " << sizeof(vertices2) << std::endl;
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

#pragma endregion object

	// Texture
	Texture texture("Res/wall.jpg");

	Shader lightShader("Shaders/LightVertex.shader", "Shaders/LightFragment.shader");
	Shader texShader("Shaders/VertTexture.shader", "Shaders/FragTexture.shader");
	Shader bennyShader("Shaders/benny/basicShader.vs", "Shaders/benny/basicShader.fs");

	Mesh box("res/testBoxNoUV.obj");
	Mesh monkey("res/monkey3.obj");

	glm::mat4 mvp = projection * view * objectModel;

	float start_time = glfwGetTime();
	
	while (!window.Closed())
	{
		window.Clear(.5f, .5f, .5f);

		double now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		float zRot = sinf(now);

		camera.KeyControl(window.getsKeys(), deltaTime);
		camera.MouseControl(window.getXChange(), window.getYChange());

		projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth()/ (float)window.GetHeight(), 0.1f, 100.0f);
		view = camera.CalculateViewMatrix();

		// Get the object transform
		glm::vec3 scale_value = glm::vec3(window.GetScaleSliderValue());
		glm::vec3 rotation_value = window.GetRotationSliderValue();
		glm::vec3 translation_value = window.GetTranslationSliderValue();
		objectTransform.SetScale(scale_value);
		objectTransform.SetRot(rotation_value);
		objectTransform.SetPos(translation_value);


		// Get the light transform
		glm::vec3 lightColor = window.GetLightColorSliderValue();
		glm::vec3 lightScale = glm::vec3(window.GetLightScaleSliderValue());
		glm::vec3 lightPosition = window.GetLightTranslationSliderValue();
		lightTransform.SetScale(lightScale);
		lightTransform.SetPos(lightPosition);
			   
		objectModel = objectTransform.GetModel();
		mvp = projection * view * objectModel;

		// Draw the object
		texShader.Use();
		texShader.SetVec3fv("model", 1, glm::value_ptr(objectModel));
		texShader.SetVec3fv("lightPosition", 1, glm::value_ptr(lightPosition));
		texShader.SetVec3fv("lightColor", 1, glm::value_ptr(lightColor));
		texShader.SetMatrix4fv("u_MVP", 1, GL_FALSE, glm::value_ptr(mvp));
		//mesh.Draw();
		monkey.Draw();
		//GLCall(glBindVertexArray(object_vao));
		//GLCall(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0));

		// Draw the light
		lightModel = lightTransform.GetModel();
		mvp = projection * view * lightModel;
		lightShader.Use();
		lightShader.SetMatrix4fv("u_MVP", 1, GL_FALSE, glm::value_ptr(mvp));
		GLCall(glBindVertexArray(light_vao));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		//mesh.Draw();

		window.Update();

	}

	return 0;
}








