#pragma once
#include <GL/glew.h>;
#include "../Logging/Printable.h";
#include "../Logging/Log.h";

template<class T>
class Texture2D : public IPrintable {
public:
	Texture2D(const GLuint _textureTargetOffset);
	~Texture2D();
	void Bind() const;
	void ImageData(T _data[], GLenum _internalFormat, GLenum _format, GLenum _type, GLsizei _width, GLsizei _height);
	void SetWrapMode(GLenum _mode);
	void SetWrapMode(GLenum _modeX, GLenum _modeY);
	void SetMipMap(GLenum _modeMin, GLenum _modeMag);
	GLuint GetTextureTargetOffset();
	GLuint GetTextureID();
public:
	// Inherited via IPrintable
	virtual std::string GetString() const override;
private:
	GLenum m_MipMapMin = GL_LINEAR;
	GLenum m_MipMapMag = GL_LINEAR;

	GLenum m_WrapModeX = GL_REPEAT;
	GLenum m_WrapModeY = GL_REPEAT;

	GLuint m_TextureID;
	GLuint m_TextureTargetOffset;
private:
	void SetWrapModes();
	void SetMipMaps();
};

template<class T>
inline Texture2D<T>::Texture2D(const GLuint _textureTargetOffset)
	: m_TextureTargetOffset(_textureTargetOffset)
{
	glGenTextures(1, &m_TextureID);
	Bind();
}

template<class T>
inline Texture2D<T>::~Texture2D()
{
	//glDeleteTextures(1, &m_TextureID);
}

template<class T>
inline void Texture2D<T>::Bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_TextureTargetOffset);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

template<class T>
inline void Texture2D<T>::ImageData(T _data[], GLenum _internalFormat, GLenum _format, GLenum _type, GLsizei _width, GLsizei _height)
{
	glTexImage2D(GL_TEXTURE_2D,
		0,
		_internalFormat,
		_width,
		_height,
		0,
		_format,
		_type,
		_data);

	SetMipMaps();
	SetWrapModes();

	glGenerateMipmap(GL_TEXTURE_2D);
}

template<class T>
void Texture2D<T>::SetWrapMode(GLenum _mode)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _mode);
}

template<class T>
void Texture2D<T>::SetWrapMode(GLenum _modeX, GLenum _modeY)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _modeX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _modeY);
}

template<class T>
inline void Texture2D<T>::SetMipMap(GLenum _modeMin, GLenum _modeMag)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _modeMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _modeMag);
}
template<class T>
inline GLuint Texture2D<T>::GetTextureTargetOffset()
{
	return m_TextureTargetOffset;
}
template<class T>
inline GLuint Texture2D<T>::GetTextureID()
{
	return m_TextureID;
}
template<class T>
inline std::string Texture2D<T>::GetString() const
{
	return std::string("Texture2D, textureID = " + std::to_string(m_TextureID));
}

template<class T>
inline void Texture2D<T>::SetWrapModes()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapModeX);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_WrapModeY);
}

template<class T>
inline void Texture2D<T>::SetMipMaps()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_MipMapMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_MipMapMag);
}
