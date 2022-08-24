#include <iostream>
#include <memory>

#include "Renderer/Window.h"
#include "Logging/Log.h"
#include "Renderer/Application.h"
#include "Renderer/Shader.h"
#include "Input/Input.h"
#include "Renderer/Texture.h"
#include "Tools/ScopeTimer.h"
#include "Renderer/Renderer.h"

constexpr auto DEBUG_TEXTURE_WIDTH = 2048;
constexpr auto DEBUG_TEXTURE_HEIGHT = 2048;
constexpr auto DEBUG_VOXEL_COUNT = 16;
constexpr auto DEBUG_VOXEL_DISTRIBUTION = 4;

class Game : public Application {
public:
    Game(Window* _applicationWindow) : Application::Application(_applicationWindow) {   }
    void Startup() override 
    {
        LOG_TIME_SCOPE();

        Input::SetCursorMode(m_applicationWindow->GetRenderContext(), false);
        Input::SetMousePositionCallback(m_applicationWindow->GetRenderContext(), this);
        Input::SetOnKeyPressedCallback(m_applicationWindow->GetRenderContext(), this);

        m_testShader.LoadShaderSource("F:\\cleanProjects\\openGLVoxels\\openGLVoxels\\res\\shaders\\default.glsl");
        std::string compilationMessage;
        GLuint program = m_testShader.Compile(&compilationMessage);
        Log::Out(LogLevel::INFO, compilationMessage);

        std::shared_ptr<GLfloat[]> testVoxelData(new GLfloat[DEBUG_TEXTURE_HEIGHT * DEBUG_TEXTURE_WIDTH * 4]);
        
        GLCall(Texture2D<GLfloat> testTex(0);
        testTex.ImageData(testVoxelData.get(), GL_RGBA32F, GL_RGBA, GL_FLOAT, DEBUG_TEXTURE_WIDTH, DEBUG_TEXTURE_HEIGHT);
        testTex.Bind());
        testTex.SetWrapMode(GL_CLAMP_TO_BORDER);
        m_texID = testTex.GetTextureID();
        m_tTO = testTex.GetTextureTargetOffset();

        static float positions[8] = {
           -1.f, 1.f,
           1.f, 1.f,
           1.f, -1.f,
           -1.f, -1.f
        };

        static GLuint indices[3 * 2] = {
            0,1,2,
            2,3,0
        };

        GLCall(buff.SubmitData(positions, 8 * sizeof(float), GL_STATIC_DRAW);)
        GLCall(VertexBufferLayout layout;)
        GLCall(layout.AddElement(VertexBufferAttribute(Shader::ShaderDataType::Float2, false));)
        GLCall(buff.SpecifyLayout(layout);)

        GLCall(iBuff.SubmitData(indices, 6, GL_STATIC_DRAW);)

        vao.AddVertexBuffer(buff);
        GLCall(vao.SetIndexBuffer(iBuff);)
        GLCall(vao.Bind();)
    }

    void Update(double _timeSinceStartup, long long _gameTicks) override
    {
        LOG_TIME_SCOPE();
        glfwGetWindowSize(m_applicationWindow->GetRenderContext(), &m_windowWidthHeight.x, &m_windowWidthHeight.y);
        glViewport(0, 0, m_windowWidthHeight.x, m_windowWidthHeight.y);

        GLCall(glUseProgram(m_testShader.GetGLProgram()););

        m_testShader.SetUniform("u_Resolution", &m_windowWidthHeight, 1);
        m_testShader.SetUniform("u_GameTime", (float)_timeSinceStartup / 1000.f);
  
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    }
    
    void OnMouseCursorMoved(double _posX, double _posY) override {
    }
    void OnKeyPressed(int _key) override {
        if (_key == GLFW_MOUSE_BUTTON_1)
            Input::SetCursorMode(m_applicationWindow->GetRenderContext(), false);
        if (_key == GLFW_KEY_ESCAPE)
            Input::SetCursorMode(m_applicationWindow->GetRenderContext(), true);
    }
    void Quit() {
    }
private:
    VertexBuffer buff;
    IndexBuffer iBuff;
    VertexArray vao;

    Shader m_testShader;
    glm::ivec2 m_windowWidthHeight;
    GLuint m_texID;
    GLuint m_tTO;
};

int main(void)
{
    Window mainWindow(1080, 720, "gaming moment");
    Game game(&mainWindow);
    game.Start();
    return 0;
}