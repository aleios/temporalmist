#include <BlockObject.hpp>

BlockObject::BlockObject(const std::string& inTexFilename)
	: GameObject(inTexFilename)
{

}

void BlockObject::Update(unsigned int timestep)
{
}

void BlockObject::Draw()
{
	sprite.Draw();
}