#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

struct particle_t;

class VBO
{
    public:
        GLuint ID{};
        VBO(const GLfloat* vertices, GLsizeiptr size);
        VBO(const particle_t* vertices, GLsizeiptr size);

        void Bind() const;
        void Unbind();
        void Delete();

        void changeArray(const GLfloat *vertices,GLsizeiptr size);
        void changeArray(const particle_t *vertices,GLsizeiptr size);
};

#endif
