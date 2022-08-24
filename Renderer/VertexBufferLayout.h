#pragma once
#include "GL/glew.h"
#include "Shader.h"

static GLuint ShaderDataTypeSize(Shader::ShaderDataType _type) {
	switch (_type) {
		case Shader::ShaderDataType::Float:    return sizeof(float);
		case Shader::ShaderDataType::Float2:   return sizeof(float) * 2;
		case Shader::ShaderDataType::Float3:   return sizeof(float) * 3;
		case Shader::ShaderDataType::Float4:   return sizeof(float) * 4;
		case Shader::ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
		case Shader::ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;
		case Shader::ShaderDataType::Int:      return sizeof(int);
		case Shader::ShaderDataType::Int2:     return sizeof(int) * 2;
		case Shader::ShaderDataType::Int3:     return sizeof(int) * 3;
		case Shader::ShaderDataType::Int4:     return sizeof(int) * 4;
		case Shader::ShaderDataType::Bool:     return sizeof(bool);
	}
	return 0;
}

struct VertexBufferAttribute {
	VertexBufferAttribute(Shader::ShaderDataType _dataType, bool _normalized = false);
	GLuint GetComponentCount() const;
	Shader::ShaderDataType GetType() const;
	GLboolean IsNormalized() const;

	GLuint Size = 0;
	GLuint Offset = 0;
private:
	Shader::ShaderDataType m_Type;
	bool m_Normalized;
};

struct VertexBufferLayout {
	std::vector<VertexBufferAttribute>::iterator begin() { return m_Elements.begin(); }
	std::vector<VertexBufferAttribute>::iterator end() { return m_Elements.end(); }
	std::vector<VertexBufferAttribute>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<VertexBufferAttribute>::const_iterator end() const { return m_Elements.end(); }

	VertexBufferLayout();
	VertexBufferLayout(std::initializer_list<VertexBufferAttribute> _elements);
	VertexBufferLayout& AddElement(VertexBufferAttribute _attributeToAdd);
	GLuint GetStride() const;
private:
	void CalculateStrideAndSetOffsets();
	GLuint m_Stride = 0;
	std::vector<VertexBufferAttribute> m_Elements;
};