#include "VAO.h"

VAO::VAO() // doesnt require a parameter
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, GLuint layout) 
{
	VBO.Bind();
	// Specify how OpenGL should interpret the vertex data
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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