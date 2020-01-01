#include <glew.h>
#include <glfw3.h>

#include <iostream>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Camera.h"

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

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
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

#pragma region IMGUI
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	const char* our_glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(our_glsl_version);

#pragma endregion IMGUI

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
	//glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	// Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetWindowUserPointer(m_window, this);

}


Window::~Window()
{
	glfwTerminate();
}

//void Window::ProcessInput()
//{
//	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(m_window, true);
//	if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
//		glfwSetWindowShouldClose(m_window, true);
//	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
//		glfwSetWindowShouldClose(m_window, true);
//	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
//		std::cout << "Left" << std::endl;
//	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//		std::cout << "Right" << std::endl;
//}

const bool Window::GetMouseHidden()
{
	return mouseHidden;
}

void Window::SetMouseHidden(bool hidden)
{
	if (hidden)
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Camera::SetLockCamera(false);
		mouseHidden = true;
	}
	else
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		Camera::SetLockCamera(true);
		mouseHidden = false;
	}

//	mouseHidden = !mouseHidden;
	mouseFirstMoved = !mouseFirstMoved;
}

void Window::Update()
{
	//ProcessInput();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
;

	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::SliderFloat("Scale", &scale_slider_value, 0.0f, 20.0f);
		ImGui::SliderFloat3("Rotation", rotation_slider_value, 0.0f, 360.0f);
		ImGui::SliderFloat3("Translation", translation_slider_value, -20.f, 20.0f);

		 //Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

int Window::GetWidth()
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return w;
}

int Window::GetHeight()
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	return h;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(m_window, handleKeys);
	glfwSetCursorPosCallback(m_window, handleMouse);
}

const float Window::GetScaleSliderValue()
{
	return scale_slider_value;
}

const glm::vec3 Window::GetRotationSliderValue()
{
	return glm::vec3(rotation_slider_value[0], rotation_slider_value[1], rotation_slider_value[2]);
}
const glm::vec3 Window::GetTranslationSliderValue()
{
	return glm::vec3(translation_slider_value[0], translation_slider_value[1], translation_slider_value[2]);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	{
		if (theWindow->GetMouseHidden())
		{
			theWindow->SetMouseHidden(false);
		}
		else
		{
			theWindow->SetMouseHidden(true);
		}
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}




