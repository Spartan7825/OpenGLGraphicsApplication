#version 330 core

// It outputs a vec4 color
out vec4 FragColor;

// Imports the vec3 input color that was given as output from the vertexShader
// It is important to give the inputs the same names as outputs otherwise openGL can't link them (Dumb)
in vec3 color;
// Imports the texture coordinates from the vertex Shader
in vec2 texCoord;

// Imports the normal from vertex shader
in vec3 Normal;
// Imports the current position  from vertex shader
in vec3 crntPos;

// Gets the texture unit from the main function
uniform sampler2D tex0;
//Gets the light color from main function
uniform vec4 lightColor;
// Gets the position of light from main function
uniform vec3 lightPos;
// Gets position of camera from main function
uniform vec3 camPos;

void main()
{
	// We give a color in RGBA format to use for all the vertices
	//FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);

	// Now instead of the above where we passed float values as arguments of vec 4 we pass 'color'
	//FragColor = vec4(color, 1.0f); //(RGB, A)

	// Ambient lighting
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	// Diffuse lighting
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}