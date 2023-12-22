#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	// The three main vectors of Camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f); // direction of camera
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// A boolean variable to pevent camera from snapping to the clicked location if its the first click
	bool firstClick = true;

	// Variables to store width, height of window
	int width, height;

	// Variables to adjust camera speed and sentivity
	float speed = 0.005f;
	float sensitivity = 75.0f;

	// Constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to vertex shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports Camera Matrix to a Shader
	void Matrix(Shader& shader, const char* uniform);
	// Handles camera input
	void Inputs(GLFWwindow* window);

};

#endif