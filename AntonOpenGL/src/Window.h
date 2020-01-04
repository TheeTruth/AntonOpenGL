#pragma once
class Window
{

private:
	int m_width, m_height;
	const char* m_title;
	struct GLFWwindow* m_window;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseHidden = true;
	bool mouseFirstMoved;
	bool keys[1024];
	bool show_demo_window = true;
	bool show_another_window = false;

	// object values
	float rotation_slider_value[3] = { 0.0f };
	float translation_slider_value[3] = { 0.0f };
	float scale_slider_value = 2.0f;

	//light values
	float color_slider_value[3] = { 1.0f, 1.0f, 1.0f };
	float light_translation_slider_value[3] = { 0.0f };
	float light_scale_slider_value = 1.0f;

public:
	Window(int width, int height, const char* title);
	~Window();

	const bool GetMouseHidden();

	void SetMouseHidden(bool hide_mouse);
	//void ProcessInput();
	void Update();
	bool Closed();
	void Clear(float r, float g, float b);
	void Init();
	int GetWidth();
	int GetHeight();

	inline bool* getsKeys() { return keys; }

	GLfloat getXChange();
	GLfloat getYChange();

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	void createCallbacks();

	const float GetScaleSliderValue();
	const glm::vec3 GetRotationSliderValue();
	const glm::vec3 GetTranslationSliderValue();

	const float GetLightScaleSliderValue();
	const glm::vec3 GetLightColorSliderValue();
	const glm::vec3 GetLightTranslationSliderValue();


};

