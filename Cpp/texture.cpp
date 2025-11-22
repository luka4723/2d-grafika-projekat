#include "texture.hpp"

Texture::Texture(const char* image, GLenum texType, GLenum texSlot, GLenum pixelType, GLenum wrap, int filter)
{
	type = texType;
	slot = texSlot;

	int w, h, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &w, &h, &nrChannels, 0);

    GLenum format;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	if(filter==1)
    {
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
    {
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, wrap);

	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(texType, 0, format, w, h, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader &shader, const char* uniform)
{
    shader.Activate();
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	glUniform1i(texUni, slot-GL_TEXTURE0);
}

void Texture::Bind()
{
    glActiveTexture(slot);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
