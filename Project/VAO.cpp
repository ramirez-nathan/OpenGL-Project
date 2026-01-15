#include "VAO.h"

VAO::VAO() // doesnt require a parameter
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// Specify how OpenGL should interpret the vertex data
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

const void VAO::Bind()
{
	glBindVertexArray(ID);
}

const void VAO::Unbind()
{
	glBindVertexArray(0);
}

const void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}