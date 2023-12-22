#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;


GLfloat vertices[] =
{
	// --- Coordinates --- //			 // --- Colors RGB --- //	 // --- TexCoord -- //    // --- Normals --- //

     -0.5f, 0.0f, 0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.0f,            0.0f, -1.0f, 0.0f,  //bottom
	 -0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.5f,            0.0f, -1.0f, 0.0f,
	  0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              5.0f,5.0f,            0.0f, -1.0f, 0.0f,
	  0.5f, 0.0f, 0.5f,                    0.83f,0.70f,0.44f,              5.0f,0.0f,            0.0f, -1.0f, 0.0f,

     -0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.0f,           -0.8f,  0.5f, 0.0f, //left
	 -0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              5.0f,0.0f,           -0.8f,  0.5f, 0.0f,
	  0.0f, 0.8f, 0.0f,                    0.92f,0.86f,0.76f,              2.5f,5.0f,           -0.8f,  0.5f, 0.0f,

	 -0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              5.0f,0.0f,            0.0f,  0.5f,-0.8f, //Non facing side
	  0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.0f,            0.0f,  0.5f,-0.8f,
	  0.0f, 0.8f, 0.0f,                    0.92f,0.86f,0.76f,              2.5f,5.0f,            0.0f,  0.5f,-0.8f,

	  0.5f, 0.0f,-0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.0f,            0.8f,  0.5f, 0.0f, //right
	  0.5f, 0.0f, 0.5f,                    0.83f,0.70f,0.44f,              5.0f,0.0f,            0.8f,  0.5f, 0.0f,
	  0.0f, 0.8f, 0.0f,                    0.92f,0.86f,0.76f,              2.5f,5.0f,            0.8f,  0.5f, 0.0f,

	  0.5f, 0.0f, 0.5f,                    0.83f,0.70f,0.44f,              5.0f,0.0f,            0.0f,  0.5f, 0.8f, //Facing Side
	 -0.5f, 0.0f, 0.5f,                    0.83f,0.70f,0.44f,              0.0f,0.0f,            0.0f,  0.5f, 0.8f,
	  0.0f, 0.8f, 0.0f,                    0.92f,0.86f,0.76f,              2.5f,5.0f,            0.0f,  0.5f, 0.8f,


};

GLuint indices[] =
{
	0, 1, 2, //Bottom
	0, 2, 3, //Bottom
	4, 5, 6, //Left
	7, 8, 9, //Non Facing
   10, 12, 11, //Right
   13, 15, 14 //Facing
};

GLfloat lightVertices[] =
{ //	COORDINATES //
   -0.1f, -0.1f,  0.1f,
   -0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f,  0.1f,
   -0.1f,  0.1f,  0.1f,
   -0.1f,  0.1f, -0.1f,
    0.1f,   0.1f, -0.1f,
    0.1f,   0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
	glfwInit();

	//Telling GLFW what OpenGL version we are using because it is dumb + using Core profile for modern functionalities we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLApplication", NULL, NULL); //Width, Height, Name, Want FullScreen or not, Last thing is not important
	if (window == NULL)
	{
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Make window the current context
	glfwMakeContextCurrent(window);

	//Loading GLAD
	gladLoadGL();

	// Telling OpenGL the area of my window that I want it to render
	glViewport(0, 0, width, height);//Bottom left corner of the window 0,0 to the top left cornder that is 800,800


	// --- Creates Shader objects --- //
	Shader shaderProgram("default.vert", "default.frag");

	//--- Generate a VAO, then Bind it --- // ----Generate VAO before the VBO (Ordering is very Important!)---- //
	VAO VAO1;
	VAO1.Bind();

	// --- Generate a VBO and link it to the vertices --- //
	VBO VBO1(vertices, sizeof(vertices));
	// --- Generate an EBO and link it to the indices --- //
	EBO EBO1(indices, sizeof(indices));

	// Link the VBO to the VAO so it can use it and then Unbind VAO,VBO, and EBO afterwards
	// (VBO1 , layout 0 for coordinates)
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	// (VBO1 , layout 1 for colors)
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	// (VBO1, layout 2 for texture coordinates)
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));

	//Texture
	Texture appliedTexture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	appliedTexture.texUnit(shaderProgram, "tex0", 0);

	// Enabling the depth buffer
	glEnable(GL_DEPTH_TEST);

	// Creates a camera object
	Camera camera(width, height, glm::vec3(0.0, 0.0, 2.0));

	//Loop to keep the window open until it is closed
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); //Navy Blue(BackBuffer) and the (FrontBuffer) has the default colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// The Camera Inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		//Tell OpenGL which program we want to use
		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");

		// Binding texture so it appears in rendering
		appliedTexture.Bind();
		//Bind the VAO so OpenGL knows how to use it
		VAO1.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window); //We swap buffers as only the pixels of (FrontBuffer) are displayed

		//Takes care of all GLFW events
		glfwPollEvents();
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	appliedTexture.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}