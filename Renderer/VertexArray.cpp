#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_VAO);)
    GLCall(glBindVertexArray(m_VAO);)
}

void VertexArray::Bind()
{
    GLCall(glBindVertexArray(m_VAO);)
}

void VertexArray::AddVertexBuffer(VertexBuffer& _VertexBuffer)
{
    Bind();
    const VertexBufferLayout& layout = _VertexBuffer.GetLayout();
    for (const VertexBufferAttribute& attrib : layout) {
        GLuint vertexAttributeArrayIdx = m_VertexBuffers.size();

        GLCall(glEnableVertexAttribArray(vertexAttributeArrayIdx);)
        GLCall(glVertexAttribPointer(vertexAttributeArrayIdx,
            attrib.GetComponentCount(),
            ShaderDataTypeToGLType(attrib.GetType()),
            attrib.IsNormalized(),
            layout.GetStride(),
            (const void*)attrib.Offset);)
    }
    m_VertexBuffers.push_back(_VertexBuffer);
}

void VertexArray::SetIndexBuffer(IndexBuffer& _IndexBuffer)
{
    m_IndexBuffer = _IndexBuffer;
}