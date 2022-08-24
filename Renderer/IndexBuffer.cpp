#include "IndexBuffer.h"
#include "Renderer.h"

void IndexBuffer::SubmitData(const GLuint* _data, GLuint _count, GLenum _drawMode)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(GLuint), _data, _drawMode);
}

IndexBuffer::IndexBuffer()
{
	glGenBuffers(1, &m_BufferID);
}

IndexBuffer::~IndexBuffer()
{
	//glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::GetIndexCount() const
{
	return m_IndexCount;
}
