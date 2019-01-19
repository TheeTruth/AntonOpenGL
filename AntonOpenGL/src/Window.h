#pragma once
class Window
{

private:
	int m_width, m_height;
	const char* m_title;
	struct GLFWwindow* m_window;

public:
	Window(int width, int height, const char* title);
	~Window();

	void ProcessInput();
	void Update();
	bool Closed();
	void Clear(float r, float g, float b);
	void Init();
};

