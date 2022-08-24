#include "Window.h"
#include "../Logging/Log.h"

Window::Window(uint16_t _width, uint16_t _height, const std::string _title) :
    m_height(_height), m_width(_width), m_title(_title)
{
    GLFWwindow* window;
    /* Initialize glfw */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // succeeded? save parameters to class
    m_title = _title;
    m_height = _height;
    m_width = _width;

    // now glew is ready to be initialized
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        Log::Out("something went wrong whilst initializing GLEW. "/*, glewGetErrorString(glewStatus)*/);
    }

    m_renderContext = window;
}

GLFWwindow* Window::GetRenderContext()
{
    return m_renderContext;
}
