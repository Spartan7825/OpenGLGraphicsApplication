// ----- Shaders can be thought of as functions that run on the GPU ----- //
#include "shaderclass.h"


// Reads a text file and outputs it as a string
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// ---------- EVERYTHING HERE SHADER RELATED ---------- //

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//Read the vertexFile and fragmentFile storing as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//Convert the shader strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to vertexShader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile vertex Shader into machine code
	glCompileShader(vertexShader);
	// Checks if shader compiled successfully
	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	// Checks if shader compiled successfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader program ang get its reference
	ID = glCreateProgram();//ID already defined in 'shaderClass.h'
	// Attach the vertex and Fragment Shaders to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	// Link all the shaders together in shader program
	glLinkProgram(ID);
	// Checks if shader linked successfully
	compileErrors(ID, "PROGRAM");

	// Delete the shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glUseProgram(ID);
}

// Check for shader errors to see if different shaders have compiled successfully
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION ERROR FOR:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;

		}
	}
}