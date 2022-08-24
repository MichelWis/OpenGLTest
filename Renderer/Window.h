#pragma once
#define GLEW_STATIC //glew is being imported as a static library.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window {
public:
	Window(uint16_t _width, uint16_t _height, const std::string _title);
	GLFWwindow* GetRenderContext();
private:
	uint16_t m_width = 0;
	uint16_t m_height = 0;
	std::string m_title = "";
	GLFWwindow* m_renderContext = NULL;
};