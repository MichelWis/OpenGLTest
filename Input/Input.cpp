#include "Input.h"

void Input::SetOnKeyPressedCallback(GLFWwindow* _window, Application* _application)
{
	glfwSetWindowUserPointer(_window, (void*)_application);
	glfwSetKeyCallback(_window, OnKeyPressedCallback);
	glfwSetMouseButtonCallback(_window, OnMouseButtonCallback);
}

void Input::SetMousePositionCallback(GLFWwindow* _window, Application* _application)
{
	glfwSetWindowUserPointer(_window, (void*)_application);
	glfwSetCursorPosCallback(_window, OnMouseCursorMovedCallback);
}

void Input::SetCursorMode(GLFWwindow* _window, bool _visible)
{
	if (!_visible)
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int Input::GetCursorMode(GLFWwindow* _window)
{
	return glfwGetInputMode(_window, GLFW_CURSOR);
}

void Input::OnKeyPressedCallback(GLFWwindow* _window, KeyCode _key, int _scancode, int _action, int _mods)
{
	Application* application = (Application*)glfwGetWindowUserPointer(_window);
	application->OnKeyPressed(_key);
}

void Input::OnMouseCursorMovedCallback(GLFWwindow* _window, double _posX, double _posY)
{
	Application* application = (Application*)glfwGetWindowUserPointer(_window);
	application->OnMouseCursorMoved(_posX, _posY);
}

void Input::OnMouseButtonCallback(GLFWwindow* _window, KeyCode _key, int _action, int _mods)
{
	Application* application = (Application*)glfwGetWindowUserPointer(_window);
	application->OnKeyPressed(_key);
}