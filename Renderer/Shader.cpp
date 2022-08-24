#include "Shader.h"

Shader::Shader() 
	: m_thisProgram(UNINITIALIZED_PROGRAM)
{   }

Shader::~Shader()
{
	//if (m_thisProgram != UNINITIALIZED_PROGRAM)
		//glDeleteProgram(m_thisProgram);
}

GLuint Shader::Compile(std::string* _compilationMessage)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;

	const char* shaderCStr;
	const GLchar* const* shaderSource;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	shaderCStr = m_vertexShaderSource.c_str();
	shaderSource = &shaderCStr;
	glShaderSource(vertexShader, 1, shaderSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderCStr = m_fragmentShaderSource.c_str();
	shaderSource = &shaderCStr;
	glShaderSource(fragmentShader, 1, shaderSource, NULL);
	glCompileShader(fragmentShader);

	if (_compilationMessage != nullptr) {
		GLint maxLength = 0;
		GLint overallLength = 0;

		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		// we need to account for the null termination char -> +1
		std::vector<GLchar> compilationLog(maxLength + 1);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &compilationLog[0]);
		if (maxLength > 0) {
			_compilationMessage->append(compilationLog.begin(), compilationLog.end()).append("\n");
			overallLength += maxLength;
		}

		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
		// we need to account for the null termination char -> +1
		compilationLog = std::vector<GLchar>(maxLength + 1);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &compilationLog[0]);

		if (maxLength > 0) {
			_compilationMessage->append(compilationLog.begin(), compilationLog.end());
			overallLength += maxLength;
		}
		if (overallLength == 0)
			_compilationMessage->append("Shader compilation successful.");
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_thisProgram = program;
	return program;
}

GLuint Shader::CompileCompute(std::string* _compilationMessage)
{
	GLuint computeShader;
	GLuint program;

	const char* shaderCStr;
	const GLchar* const* shaderSource;

	computeShader = glCreateShader(GL_COMPUTE_SHADER);
	shaderCStr = m_computeShaderSource.c_str();
	shaderSource = &shaderCStr;
	glShaderSource(computeShader, 1, shaderSource, NULL);
	glCompileShader(computeShader);


	if (_compilationMessage != nullptr) {
		GLint maxLength = 0;

		glGetShaderiv(computeShader, GL_INFO_LOG_LENGTH, &maxLength);
		// we need to account for the null termination char -> +1
		std::vector<GLchar> compilationLog(maxLength + 1);
		glGetShaderInfoLog(computeShader, maxLength, &maxLength, &compilationLog[0]);
		if (maxLength > 0) {
			_compilationMessage->append(compilationLog.begin(), compilationLog.end()).append("\n");
		}
		else {
			_compilationMessage->append("compute shader compilation successful.");
		}
	}
	program = glCreateProgram();
	glAttachShader(program, computeShader);
	glLinkProgram(program);

	glDeleteShader(computeShader);

	m_thisProgram = program;
	return program;
}

GLuint Shader::GetGLProgram()
{
	return m_thisProgram;
}

void Shader::LoadShaderSource(const char* _sourceFilePath)
{
	enum class ShaderType {
		NONE=-1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream shaderFileStream (_sourceFilePath);
	std::string currentLine;

	ShaderType mode = ShaderType::NONE;
	// stringstreams for vertex and fragment shader
	std::stringstream shaderStreams[2];

	int t = 0;
	while (getline(shaderFileStream, currentLine)) {
		t++;
		if (currentLine.find("#ShaderType") != std::string::npos) {
			if (currentLine.find("Vertex") != std::string::npos) {
				mode = ShaderType::VERTEX;
			}
			else if (currentLine.find("Fragment") != std::string::npos) {
				mode = ShaderType::FRAGMENT;
			}
			else {
				mode = ShaderType::NONE;
			}
		}
		// If line doesn't contain a shader type declaration, interpret it as a <mode> shader.
		else if(mode != ShaderType::NONE) {
			shaderStreams[(int)mode] << currentLine << "\n";
		}
	}

	m_vertexShaderSource = shaderStreams[(int)ShaderType::VERTEX].str();
	m_fragmentShaderSource = shaderStreams[(int)ShaderType::FRAGMENT].str();

	Log::Out(LogLevel::MESSAGE, "\n", m_vertexShaderSource);
	Log::Out(LogLevel::MESSAGE, "\n", m_fragmentShaderSource);
}

void Shader::LoadShaderSourceCompute(const char* _sourceFilePath)
{
	enum class ShaderType {
		NONE = -1, COMPUTE = 0
	};

	std::ifstream shaderFileStream(_sourceFilePath);
	std::string currentLine;

	ShaderType mode = ShaderType::NONE;
	// stringstreams for vertex and fragment shader
	std::stringstream shaderStream;

	int t = 0;
	while (getline(shaderFileStream, currentLine)) {
		t++;
		if (currentLine.find("#ShaderType") != std::string::npos) {
			if (currentLine.find("Compute") != std::string::npos) {
				mode = ShaderType::COMPUTE;
			}
		}
		// If line doesn't contain a shader type declaration, interpret it as a <mode> shader.
		else if (mode != ShaderType::NONE) {
			shaderStream << currentLine << "\n";
		}
	}

	m_computeShaderSource = shaderStream.str();
	Log::Out(LogLevel::MESSAGE, "\n", m_computeShaderSource);
}

void Shader::SetUniform(const GLchar* _uniformName, float _val)
{
	glUniform1f(GetUniform(_uniformName), _val);
}
void Shader::SetUniform(const GLchar* _uniformName, int _val)
{
	glUniform1i(GetUniform(_uniformName), _val);
}
void Shader::SetUniform(const GLchar* _uniformName, float _val0, float _val1, float _val2)
{
	glUniform3f(GetUniform(_uniformName), _val0, _val1, _val2);
}

void Shader::SetUniform(const GLchar* _uniformName, float _val0, float _val1, float _val2, float _val3)
{
	glUniform4f(GetUniform(_uniformName), _val0, _val1, _val2, _val3);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::vec2* _val, GLuint _cnt)
{
	glUniform2fv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::vec3* _val, GLuint _cnt)
{
	glUniform3fv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::vec4* _val, GLuint _cnt)
{
	glUniform4fv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::ivec2* _val, GLuint _cnt)
{
	glUniform2iv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::ivec3* _val, GLuint _cnt)
{
	glUniform3iv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

void Shader::SetUniform(const GLchar* _uniformName, glm::ivec4* _val, GLuint _cnt)
{
	glUniform4iv(GetUniform(_uniformName), _cnt, &_val[0].x);
}

GLint Shader::GetUniform(const GLchar* _uniformName) const
{
	if (m_UniformLocationCache.find(_uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[_uniformName];
	GLint location = glGetUniformLocation(m_thisProgram, _uniformName);
	if (location > -1)
		m_UniformLocationCache.insert(std::make_pair<std::string, GLuint>(_uniformName, (GLuint)location));
	return location;
}
