#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App {
public:
	App();
	~App();

	void run();

private:
	void poll_events();

	GLFWwindow* m_window;
};