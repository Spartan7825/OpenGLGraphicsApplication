#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType)
{
	// Assigns the type of texture to the texture objects
	type = texType;
	// Stores width, height, number of color channels of image
	int widthImg, heightImg, numColorChannels;
	//OpenGL reads a texture from bottom left moving to top right while stb does that from top left to bottom right so we fix this by:
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColorChannels, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a texture unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	//(Type of texture, texture value)
	glBindTexture(texType, ID);

	//(Type of our texture, the setting we want to modify, and the value we want to give to our setting)
	//for the setting MIN_FILTER and MAG_FILTER you can choose either GL_NEAREST(pixelated for pixel art) or GL_LINEAR(That makes the texture a bit blurry)
	// in other words configuress the type of algorith used to minimise and magnify the texture (make is smaller or bigger)
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//for the setting TEXTURE_WRAP_(S,T,R axis) you can choose either GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE and GL_CLAMP_TO_BORDER
	// S,T,R axis = X,Y,Z axis
	// Configures the way in which the texture will repeat
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// In order to use GLClamp to order we have to use GLTExParameterfv (if GL_CLAMP_TO_BORDER is required)
	//float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// generate Mipmaps
	glGenerateMipmap(texType);

	// Deletes the image data as it already is in the openGL texture object
	stbi_image_free(bytes);
	// Unbind the openGL texture object
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader requires to be actvated before changing the value of a uniform
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	//Binding the texture0 uniform
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	//Binding the texture0 uniform
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	//Binding the texture0 uniform
	glDeleteTextures(1, &ID);
}