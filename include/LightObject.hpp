#ifndef LIGHTOBJECT_HPP
#define LIGHTOBJECT_HPP

#include <GameObject.hpp>

class LightObject
	: public GameObject
{
public:
	LightObject(const std::string& inTexFilename);

	void Update(unsigned int timeElapsed);
	void Draw();
};

#endif