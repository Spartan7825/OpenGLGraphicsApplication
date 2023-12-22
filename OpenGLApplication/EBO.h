#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of EBO
	GLuint ID;

	// Constructor that generates EBO and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	//Binds the EBO
	void Bind();
	//Unbinds the EBO
	void Unbind();
	//Deletes the EBO
	void Delete();
};




#endif