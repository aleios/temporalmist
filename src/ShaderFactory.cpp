#include <ShaderFactory.hpp>

std::map<std::string, Shader *> ShaderFactory::Shaders;

void ShaderFactory::Register(std::string name, const std::string& vertFilename, const std::string& fragFilename)
{
	if (Shaders.find(name) != Shaders.end())
		return;

	Shader *shader = new Shader();
	shader->Load(vertFilename, fragFilename);

	Shaders.insert(std::pair<std::string, Shader *>(name, shader));
}

Shader *ShaderFactory::Get(std::string name)
{
	if (Shaders.find(name) == Shaders.end())
		return NULL;

	return Shaders.find(name)->second;
}

void ShaderFactory::Free()
{
	std::map<std::string, Shader *>::iterator itr = Shaders.begin();

	while (itr != Shaders.end())
	{
		Shader *shader = itr->second;

		if (shader != NULL)
			delete shader;

		itr++;
	}

	Shaders.clear();
}
