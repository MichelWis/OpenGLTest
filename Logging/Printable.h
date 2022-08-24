#pragma once
#include <string>
#include <sstream>
#include <GL/glew.h>

class IPrintable {
public:
	virtual std::string GetString() const = 0;
};

template<typename T>
class Printable {
public:	
	Printable(const T& _obj) : m_obj(_obj) {	}
	
	std::string GetString() const;
private:
	const T& m_obj;

	std::string GetPointerString() const
	{
		std::stringstream pointerStream;
		pointerStream << (void const*)&m_obj;
		return "Object at: < " + std::string(pointerStream.str()) + std::string(" >");
	}
};

template<>
inline std::string Printable<const char*>::GetString() const
{
	return std::string(m_obj);
}

template<>
inline std::string Printable<const GLubyte*>::GetString() const
{
	return std::string((const char*)m_obj);
}

template<>
inline std::string Printable<GLenum>::GetString() const
{
	return std::to_string((int)m_obj);
}

template<>
inline std::string Printable<bool>::GetString() const
{
	return std::to_string(m_obj);
}template<>
inline std::string Printable<int>::GetString() const
{
	return std::to_string(m_obj);
}

template<>
inline std::string Printable<float>::GetString() const
{
	return std::to_string(m_obj);
}

template<>
inline std::string Printable<double>::GetString() const
{
	return std::to_string(m_obj);
}

template<>
inline std::string Printable<long long>::GetString() const
{
	return std::to_string(m_obj);
}

template<>
inline std::string Printable<std::string>::GetString() const
{
	return m_obj;
}

// unknown type? print address of object in memory
template<typename T>
inline std::string Printable<T>::GetString() const
{
	if (std::is_base_of<IPrintable, T>()) {
		IPrintable* obj = (IPrintable*)&m_obj;
		return obj->GetString();
	}
	return GetPointerString();
}