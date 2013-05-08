#include <Shader.hpp>

Shader::Shader()
{
	programID = 0;
	vertID = 0;
	fragID = 0;
}

Shader::~Shader()
{
	glDetachShader(programID, vertID);
	glDetachShader(programID, fragID);
	glDeleteShader(vertID);
	glDeleteShader(fragID);
	glDeleteProgram(programID);
}

void Shader::Bind()
{
	glUseProgram(programID);
}

void Shader::Unbind()
{
	glUseProgram(0);
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