#ifndef BLOCKOBJECT_HPP
#define BLOCKOBJECT_HPP

#include <GameObject.hpp>

class BlockObject
	: public GameObject
{
public:
	BlockObject(const std::string& inTexFilename);

	void Draw();
	void Update(unsigned int timestep);
private:
};

#endif