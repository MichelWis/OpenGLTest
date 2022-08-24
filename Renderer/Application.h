#pragma once
#define GLEW_STATIC //glew is being imported as a static library.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "Window.h"
#include "../Input/Input.h"

class Application {
public:
	void Start();
protected:
	Application(Window* _applicationWindow);
	/// <summary>
	/// Starts the application on the assigned window.
	/// </summary>
	virtual void Startup() = 0;
	virtual void Update(double _deltaTime, long long _gameTicks) = 0;
	virtual void Quit() {}
	Window* m_applicationWindow;
protected:
	friend class Input;
	virtual void OnKeyPressed(int _key) {}
	virtual void OnMouseCursorMoved(double _posX, double _posY) {}
};
