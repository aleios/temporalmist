#include <Shader.hpp>
#include <fstream>
#include <iostream>

Shader::Shader()
	: programID(0), vertID(0), fragID(0)
{
}

Shader::Shader(const std::string& vertFilename, const std::string& fragFilename)
{
	Load(vertFilename, fragFilename);
}

Shader::~Shader()
{
	Unload();
}

std::string Shader::ReadShader(const std::string& filename) const
{
	std::ifstream file(filename);
	std::string shader = "";

	std::string line = "";
	while(std::getline(file, line))
	{
		shader += line + "\n";
	}
	return shader;
}

void Shader::Bind()
{
	glUseProgram(programID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::Load(const std::string& vertFilename, const std::string& fragFilename)
{
	// Unload any previous instance.
	Unload();

	// Create the program.
	programID = glCreateProgram();

	// Load the vertex shader.
	vertID = glCreateShader(GL_VERTEX_SHADER);
	std::string vsource = ReadShader(vertFilename);
	const char* vstr = vsource.c_str();
	glShaderSource(vertID, 1, &vstr, 0);

	// Load the fragment shader.
	fragID = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fsource = ReadShader(fragFilename);
	const char* fstr = fsource.c_str();
	glShaderSource(fragID, 1, &fstr, 0);

	// Compile the shaders.
	glCompileShader(vertID);
	
#ifdef _DEBUG
	char vertLog[2048];
	glGetShaderInfoLog(vertID, 2048, NULL, vertLog);
	std::cout << "Vertex Shader Status: \n" << vertLog << "\n";
#endif
	

	glCompileShader(fragID);

#ifdef _DEBUG
	char fragLog[2048];
	glGetShaderInfoLog(fragID, 2048, NULL, fragLog);
	std::cout << "Fragment Shader Status: \n" << fragLog << "\n";
#endif

	// Attach the shaders.
	glAttachShader(programID, vertID);
	glAttachShader(programID, fragID);

	// Link the shaders.
	glLinkProgram(programID);

#ifdef _DEBUG
	char progLog[2048];
	glGetProgramInfoLog(programID, 2048, 0, progLog);
	std::cout << "Shader Program Status: \n" << progLog << "\n";
#endif
}

void Shader::Unload()
{
	glDetachShader(programID, vertID);
	glDetachShader(programID, fragID);
	glDeleteShader(vertID);
	glDeleteShader(fragID);
	glDeleteProgram(programID);
}

GLuint Shader::GetParameterLocation(const std::string& name) const
{
	return glGetUniformLocation(programID, name.c_str());
}

GLuint Shader::GetAttributeLocation(const std::string& name) const
{
	return glGetAttribLocation(programID, name.c_str());
}

void Shader::SetParameter(const std::string& name, float x)
{
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform1f(loc, x);
}

void Shader::SetParameter(const std::string& name, float x, float y)
{
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform2f(loc, x, y);
}

void Shader::SetParameter(const std::string& name, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform3f(loc, x, y, z);
}

void Shader::SetParameter(const std::string& name, float x, float y, float z, float w)
{
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniform4f(loc, x, y, z, w);
}

void Shader::SetParameter(const std::string& name, float* fv)
{
	GLint loc = glGetUniformLocation(programID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, fv);
}