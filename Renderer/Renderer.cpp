#include "Renderer.h"

Renderer::Renderer()   {   }



GLenum ShaderDataTypeToGLType(Shader::ShaderDataType _type) {
    switch (_type) {
    case Shader::ShaderDataType::Float:
        return GL_FLOAT;
    case Shader::ShaderDataType::Float2:
        return GL_FLOAT;
    case Shader::ShaderDataType::Float3:
        return GL_FLOAT;
    case Shader::ShaderDataType::Float4:
        return GL_FLOAT;
    case Shader::ShaderDataType::Mat3:
        return GL_FLOAT;
    case Shader::ShaderDataType::Mat4:
        return GL_FLOAT;
    case Shader::ShaderDataType::Int:
        return GL_INT;
    case Shader::ShaderDataType::Int2:
        return GL_INT;
    case Shader::ShaderDataType::Int3:
        return GL_INT;
    case Shader::ShaderDataType::Int4:
        return GL_INT;
    case Shader::ShaderDataType::Bool:
        return GL_BOOL;
    }

    return 0;
}