#ifndef PLANKOBJECT_HPP
#define PLANKOBJECT_HPP

#include <GameObject.hpp>

class PlankObject
	: public GameObject
{
public:
	PlankObject(const std::string& inTexFilename);

	void Draw();
	void Update(unsigned int timestep);
};

#endif