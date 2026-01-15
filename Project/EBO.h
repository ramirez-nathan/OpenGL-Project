#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>	

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	const void Bind();
	const void Unbind();
	const void Delete();
};

#endif