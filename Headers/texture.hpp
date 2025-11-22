#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include "stb_image.hpp"

#include"shader.hpp"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum slot;
	Texture(const char* image, GLenum texType, GLenum texSlot, GLenum pixelType, GLenum wrap, int filter);

	void texUnit(Shader& shader, const char* uniform);
	void Bind();
	void Unbind();
	void Delete();
};
#endif
