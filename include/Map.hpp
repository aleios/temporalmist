#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <rapidxml.hpp>
#include <zlib.h>

#include <Layer.hpp>
#include <Tileset.hpp>

class Map
{
public:
	Map(const std::string& inFilename);
	~Map();

	void Draw();
	void DrawLayer(int index);

	std::vector<Layer> layers;
	std::vector<Tileset> tilesets;
private:
	rapidxml::xml_document<> mapXML;

	std::string UncompressData(std::string data);

	unsigned int width, height, tileWidth, tileHeight;
};

#endif