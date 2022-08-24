#pragma once
#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer();
	void SubmitData(const GLuint* _data, GLuint _count, GLenum _drawMode);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	GLuint GetIndexCount() const;
private:
	GLuint m_BufferID = 0;
	GLuint m_IndexCount = 0;
};