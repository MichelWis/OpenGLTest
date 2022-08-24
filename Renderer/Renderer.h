#pragma once
#define GLEW_STATIC //glew is being imported as a static library.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Logging/Log.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Window.h"
#include "glm/glm.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define DEBUG

#ifdef DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall())
#else
#define GLCall(x) x;
#endif

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall() {
    while (GLenum error = glGetError()) {
        Log::Out(LogLevel::ERROR, "[OPENGL ERROR]: ", error);
        return false;
    }
    return true;
}

GLenum ShaderDataTypeToGLType(Shader::ShaderDataType _type);

class Renderer {
private:
public:
	Renderer();
   // void Draw(VertexArray& _VertexArray, IndexBuffer& _IndexBuffer, Shader _Shader);
   // void Clear(glm::vec4 _clearColor);
};