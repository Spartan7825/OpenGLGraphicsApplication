// Similar syntax to C
#version 330 core

// layout helps openGL read the vertex data it receives
// This line takes an input aPos using the layout with location 0
// So on the 0th layout there is a vec3 data type for positions

layout (location = 0) in vec3 aPos;

// Adding a second Layout with location 1 that takes a vec3 color

layout (location = 1) in vec3 aColor;

// Adding a third Layout with location 2 that takes a vec2 aTex for texture coordinates

layout(location = 2) in vec2 aTex;


layout (location = 3) in vec3 aNormal;

// Since the fragmentShader takes care of the colors we need to output the colors from the vertexShadere to the fragmentShader

out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;


out vec3 Normal;
out vec3 crntPos;

// Imports the camera matrix from the main fucntion
uniform mat4 camMatrix;
uniform mat4 model;


void main()
{
	// Simply assign gl_Position a vec4 with all our positions + and arbitary 1 for the 4th dimension
	// openGL recognises the keyword 'gl_Position' and knows that it needs to use it as the position for the vertex
	// What adding each coordinate  the corresponding coordinate and multiplying it with scale does is that it increases the size of our trianlge [for e.g. if the scale is 0.5 then our triangles are 50% bigger]
	//gl_Position = vec4(aPos.x + aPos.x * scale , aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	//gl_Position = proj * view * model * vec4(aPos, 1.0);
	
	
	crntPos = vec3(model * vec4(aPos, 1.0f));


	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);

	//Make color = aColor imported from the vertices array
	// Assigns the color from the vertext Data to "color" that is then send out to fragment Shader
	color = aColor;
	// Assigns the texture coordinates from the vertex Data to texCoord
	texCoord = aTex;
	Normal = aNormal;
}