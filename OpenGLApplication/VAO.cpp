#include "VAO.h"

// Constructor to generate VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO attribute to the VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();

	glVertexAttribPointer(
		layout, //(the layout we are using (0 for positions and 1 for color in this case)
		numComponents, // number of components per layout(3 for positions x,y,z and 3 for color R,G,B)
		type, // Then the type of our components(GL_Float in most cases)
		GL_FALSE,
		stride, // 'Stride' here is size in bytes of each vertex (in this case 6(since each vertex has 6 floats [positions x,y,z] and [color R,G,B]))
		offset); // The offset is simply the initial offset of a layout in bytes [for the coordinates its 0 because they are at the beginning], [for the color it will be 3 times the size of float in bytes (3 * 4 = 12) since it comes after the 3 coordinates x,y,z]

	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}