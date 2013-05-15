#include <Shader.hpp>
#include <map>

class ShaderFactory
{
private:
	static std::map<std::string, Shader *> Shaders;

public:
	static void Register(std::string name, const std::string& vertFilename, const std::string& fragFilename);
	static Shader *Get(std::string name);

	static void Free();
};