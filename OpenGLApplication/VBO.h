#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
	// Reference ID of the VBO
	GLuint ID;

	// Constructor to generate a VBO and link it to the vertices (openGL takes the size as GLsizeiptr data type)
	VBO(GLfloat* vertices, GLsizeiptr size);


	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};


#endif