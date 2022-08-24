#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

class VertexArray {
public:
	VertexArray();
	void Bind();
	void AddVertexBuffer(VertexBuffer& _VertexBuffer);
	void SetIndexBuffer(IndexBuffer& _IndexBuffer);
private:
	GLuint m_VAO;
	std::vector<VertexBuffer> m_VertexBuffers;
	IndexBuffer m_IndexBuffer;
};