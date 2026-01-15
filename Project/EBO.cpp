#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // bind buffer to target buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

const void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

const void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

const void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}