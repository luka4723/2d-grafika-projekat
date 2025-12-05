#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>

#include"shader.hpp"

class Texture
{
public:
	GLuint ID{};
	GLenum type;
	GLenum slot;
	Texture(const char* image, GLenum texType, GLenum texSlot, GLenum pixelType, GLenum wrap, int filter);

	void texUnit(const Shader& shader, const char* uniform) const;
	void Bind() const;
	void Unbind() const;
	void Delete() const;
};
#endif
