#version 330 core

// It outputs a vec4 color
out vec4 FragColor;

// Taking the vec3 input color that was given as output from the vertexShader
// It is important to give the inputs the same names as outputs otherwise openGL can't link them (Dumb)
in vec3 color;
// Inputs the texture coordinates from the vertex Shader
in vec2 texCoord;

// Gets the texture unit from the main function
uniform sampler2D tex0;

void main()
{
	// We give a color in RGBA format to use for all the vertices
	//FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);

	// Now instead of the above where we passed float values as arguments of vec 4 we pass 'color'
	//FragColor = vec4(color, 1.0f); //(RGB, A)

	FragColor = texture(tex0, texCoord);
}