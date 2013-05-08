#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Asset.hpp"

class Shader
	: public Asset
{
public:
	Shader();
	Shader(const Shader& other);
	~Shader();

	Shader& operator=(const Shader& other);

	void Bind();
	void Unbind();

	GLuint GetParameterLocation(const std::string& name) const;
	GLuint GetAttributeLocation(const std::string& name) const;

	void SetParameter(const std::string& name, float x);
	void SetParameter(const std::string& name, float x, float y);
	void SetParameter(const std::string& name, float x, float y, float z);
	void SetParameter(const std::string& name, float x, float y, float z, float w);
	void SetParameter(const std::string& name, float* fv);

protected:
	void Load(const std::string& filename);
	void Unload();

private:
	GLuint programID, vertID, fragID, geomID, tcID, teID;

	std::string ReadFile(const std::string& filename) const;
};

#endif