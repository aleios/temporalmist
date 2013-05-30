#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>

#include <rapidxml.hpp>
#include <zlib.h>

#include <Tileset.hpp>
#include <Rect.hpp>

class Layer;
class GameplayState;

class Map
{
public:
	Map();
	Map(GameplayState* inParent, const std::string& inFilename);
	~Map();

	void Load(const std::string& inFilename);

	void Draw();
	void DrawLayer(int index);

	std::vector<Layer*> layers;
	std::vector<Tileset> tilesets;

	std::vector<Rect> collisionTiles, exitTiles;
private:
	rapidxml::xml_document<> mapXML;

	std::string UncompressData(std::string data);

	unsigned int width, height, tileWidth, tileHeight;
	GameplayState* parent;
	Vector2 playerStart;
};

#endif