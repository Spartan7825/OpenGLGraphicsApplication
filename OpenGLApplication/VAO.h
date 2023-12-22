#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h" // This is included beacuse we need to link the VBO to VAO

class VAO
{
public:
	// ID reference for the VAO
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO attribute to the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};



#endif
