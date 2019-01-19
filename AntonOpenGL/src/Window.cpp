#include <glew.h>
#include <glfw3.h>
#include "Window.h"
#include <iostream>

void error_callback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* title)
{
	m_width = width;
	m_height = height;
	m_title = title;

}

void Window::Init()
{
	glewExperimental = true;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vmode = glfwGetVideoMode(monitor);


	//m_window = glfwCreateWindow(vmode->width, vmode->height, m_title, monitor, NULL);
	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);

	// makes the context current
	glfwMakeContextCurrent(m_window);

	// start GLEW extension handler
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW \n");
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);  // get renderer string
	const GLubyte* version = glGetString(GL_VERSION);  // version as a string
	printf("Renderer: %s", renderer);
	printf("OpenGL version supported %s", version);

	//tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST);  // enable depth-testing
	glDepthFunc(GL_LESS);  // depth-testing interprets a smaller value as "closer"

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
}


Window::~Window()
{
	glfwTerminate();
}

void Window::ProcessInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}
void Window::Update()
{
	ProcessInput();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);

	/* Poll for and process events */
	glfwPollEvents();
}

bool Window::Closed()
{
	return glfwWindowShouldClose(m_window) == 1;
}

void Window::Clear(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



