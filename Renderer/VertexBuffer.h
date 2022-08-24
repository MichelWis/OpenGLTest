#pragma once
#include <GL/glew.h>
#include "VertexBufferLayout.h"

class VertexBuffer {
public:
	VertexBuffer();
	void SubmitData(const GLvoid* _data, GLuint _size, GLenum _drawMode);
	void SpecifyLayout(const VertexBufferLayout _layout);
	VertexBufferLayout& GetLayout();
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
private:
	GLuint m_BufferID = 0;
	VertexBufferLayout m_Layout;
};