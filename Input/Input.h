#pragma once
#define GLEW_STATIC //glew is being imported as a static library.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer/Application.h"

typedef int KeyCode;

class Input {
public:
	friend class Application;
	static void SetOnKeyPressedCallback(GLFWwindow* _window, Application* _application);
	static void SetMousePositionCallback(GLFWwindow* _window, Application* _application);
	static void SetCursorMode(GLFWwindow* _window, bool _visible);
	static int GetCursorMode(GLFWwindow* _window);
private:
	static void OnKeyPressedCallback(GLFWwindow* _window, KeyCode _key, int _scancode, int _action, int _mods);
	static void OnMouseCursorMovedCallback(GLFWwindow* _window, double _posX, double _posY);
	static void OnMouseButtonCallback(GLFWwindow* _window, KeyCode _key, int, int);
};