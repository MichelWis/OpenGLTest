#include "VertexBuffer.h"
#include "../Logging/Log.h"

VertexBuffer::VertexBuffer()
	: m_BufferID(0)
{
	glGenBuffers(1, &m_BufferID);
}

void VertexBuffer::SubmitData(const GLvoid* _data, GLuint _size, GLenum _drawMode)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, _size, _data, _drawMode);
}

void VertexBuffer::SpecifyLayout(const VertexBufferLayout _layout)
{
	m_Layout = _layout;
}

VertexBufferLayout& VertexBuffer::GetLayout()
{
	return m_Layout;
}

VertexBuffer::~VertexBuffer()
{
	//glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
