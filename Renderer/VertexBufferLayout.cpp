#include "VertexBufferLayout.h"

VertexBufferAttribute::VertexBufferAttribute(Shader::ShaderDataType _dataType, bool _normalized)
	: m_Type(_dataType), Size(ShaderDataTypeSize(_dataType)), m_Normalized(_normalized)
{   }

uint32_t VertexBufferAttribute::GetComponentCount() const
{
	switch (m_Type)
	{
	case Shader::ShaderDataType::Float:   return 1;
	case Shader::ShaderDataType::Float2:  return 2;
	case Shader::ShaderDataType::Float3:  return 3;
	case Shader::ShaderDataType::Float4:  return 4;
	case Shader::ShaderDataType::Mat3:    return 3; // ! 3* float3
	case Shader::ShaderDataType::Mat4:    return 4; // ! 4* float4
	case Shader::ShaderDataType::Int:     return 1;
	case Shader::ShaderDataType::Int2:    return 2;
	case Shader::ShaderDataType::Int3:    return 3;
	case Shader::ShaderDataType::Int4:    return 4;
	case Shader::ShaderDataType::Bool:    return 1;
	}

	return 0;
}
Shader::ShaderDataType VertexBufferAttribute::GetType() const
{
	return m_Type;
}

GLboolean VertexBufferAttribute::IsNormalized() const
{
	return m_Normalized ? GL_TRUE : GL_FALSE;
}

VertexBufferLayout::VertexBufferLayout()
{
}

VertexBufferLayout::VertexBufferLayout(std::initializer_list<VertexBufferAttribute> _elements)
	: m_Elements(_elements)
{
	CalculateStrideAndSetOffsets();
}

VertexBufferLayout& VertexBufferLayout::AddElement(VertexBufferAttribute _attributeToAdd)
{
	m_Elements.push_back(_attributeToAdd);
	return *this;
}

GLuint VertexBufferLayout::GetStride() const
{
	return m_Stride;
}

void VertexBufferLayout::CalculateStrideAndSetOffsets()
{
	m_Stride = 0;

	for (auto& element : m_Elements) {
		// current stride = offset of element because elements are enumerated and stride incremented step-by-step
		element.Offset = m_Stride;
		m_Stride += element.Size;
	}
}