#pragma once
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

#include "../Logging/Log.h"

#include "glm/glm.hpp"

#define MAX_DEBUG_LEN 512
#define UNINITIALIZED_PROGRAM std::numeric_limits<GLuint>::max()

class Shader {
public:
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
public:
	Shader();
	~Shader();
	/// <summary>
	/// Compiles the loaded shader source.
	/// </summary>
	/// <returns>Compiled and liked OpgenGL program</returns>
	GLuint Compile(std::string* _compilationMessage);
	GLuint CompileCompute(std::string* _compilationMessage);
	GLuint GetGLProgram();
	void LoadShaderSource(const char* _sourceFile);
	void LoadShaderSourceCompute(const char* _sourceFile);
	
	// The little "hack" that uses &gvecx[0].x only works because gvecx only contains x elements of type g.
	// therefore, the pointer to the first element points to the beginning of elements stored in contiguous memory
	void SetUniform(const GLchar* _uniformName, int _val);
	void SetUniform(const GLchar* _uniformName, float _val);
	void SetUniform(const GLchar* _uniformName, float _val0, float _val1, float _val2);
	void SetUniform(const GLchar* _uniformName, float _val0, float _val1, float _val2, float _val3);

	void SetUniform(const GLchar* _uniformName, glm::vec2* _val, GLuint _cnt);
	void SetUniform(const GLchar* _uniformName, glm::vec3* _val, GLuint _cnt);
	void SetUniform(const GLchar* _uniformName, glm::vec4* _val, GLuint _cnt);

	void SetUniform(const GLchar* _uniformName, glm::ivec2* _val, GLuint _cnt);
	void SetUniform(const GLchar* _uniformName, glm::ivec3* _val, GLuint _cnt);
	void SetUniform(const GLchar* _uniformName, glm::ivec4* _val, GLuint _cnt);

	GLint GetUniform(const GLchar* _uniformName) const;
private:
	mutable std::unordered_map<std::string, GLuint> m_UniformLocationCache;
	std::string m_vertexShaderSource;
	std::string m_fragmentShaderSource;
	std::string m_computeShaderSource;
	GLuint m_thisProgram;
};