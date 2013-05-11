#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertFilename, const std::string& fragFilename);
	~Shader();

	void Bind();
	void Unbind();

	void Load(const std::string& vertFilename, const std::string& fragFilename);

	GLuint GetParameterLocation(const std::string& name) const;
	GLuint GetAttributeLocation(const std::string& name) const;

	void SetParameter(const std::string& name, float x);
	void SetParameter(const std::string& name, float x, float y);
	void SetParameter(const std::string& name, float x, float y, float z);
	void SetParameter(const std::string& name, float x, float y, float z, float w);
	void SetParameter(const std::string& name, float* fv);

private:
	GLuint programID, vertID, fragID;

	std::string Shader::ReadShader(const std::string& filename) const;
	void Unload();
};

#endif