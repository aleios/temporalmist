#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

#include <Tile.hpp>

class Layer
{
public:
	Layer(const std::string inName, int inWidth, int inHeight)
		: name(inName), width(inWidth), height(inHeight)
	{
	}

	const std::string& GetName() const
	{
		return name;
	}

	const int GetWidth() const
	{
		return width;
	}

	const int GetHeight() const
	{
		return height;
	}

	std::vector<Tile> tiles;
private:
	std::string name;
	unsigned int width, height;
};

#endif