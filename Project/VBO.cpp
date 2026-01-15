#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID); // bind buffer to target buffer object
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

const void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

const void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}