#include "Application.h"
#include "../Logging/Log.h"

Application::Application(Window* _applicationWindow)
	: m_applicationWindow(_applicationWindow)
{
}
void Application::Start()
{
	glfwSetWindowUserPointer(m_applicationWindow->GetRenderContext(), this);
	Startup();

	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	high_resolution_clock gameClock;
	auto initialTimePoint = gameClock.now();
	long long gameTicks = 1;
	while (!glfwWindowShouldClose(m_applicationWindow->GetRenderContext())) {
		auto currentTimePoint = gameClock.now();
		duration<double, std::milli> timeSinceStartup = currentTimePoint - initialTimePoint;

		glClear(GL_COLOR_BUFFER_BIT);

		Update(timeSinceStartup.count(), gameTicks);
		/* Swap front and back buffers */
		glfwSwapInterval(1);
		glfwSwapBuffers(m_applicationWindow->GetRenderContext());

		/* Poll for and process events */
		glfwPollEvents();
		gameTicks++;
	}

	Quit();
	glfwTerminate();
}