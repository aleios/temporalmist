#include <Map.hpp>
#include <fstream>

Map::Map(const std::string& inFilename)
{
	// Load the XML from the map file.
	std::ifstream fs(inFilename.c_str());
	std::vector<char> buffer((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());
	buffer.push_back('\0'); // Null terminate the string.
	fs.close();

	// Parse the XML.
	mapXML.parse<0>(&buffer[0]);

	// Load the map node.
	rapidxml::xml_node<>* mapNode = mapXML.first_node("map", 0, false);

	// Get the map attributes.
	rapidxml::xml_attribute<>* attrWidth = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrHeight = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrTileWidth = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrTileHeight = mapNode->first_attribute("width", 0, false);

	this->width = (unsigned int)strtol(attrWidth->value(), 0, 10);
	this->height = (unsigned int)strtol(attrHeight->value(), 0, 10);
	this->tileWidth = (unsigned int)strtol(attrTileWidth->value(), 0, 10);
	this->tileHeight = (unsigned int)strtol(attrTileHeight->value(), 0, 10);

	
	////////////////////
	// Tilesets
	////////////////////
	rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset", 0, false);

	while(tilesetNode != 0)
	{
		Tileset tileset;

		// Get the tileset attributes.
		rapidxml::xml_attribute<>* attrFirstGID = tilesetNode->first_attribute("firstgid", 0, false);
		rapidxml::xml_attribute<>* attrName = tilesetNode->first_attribute("name", 0, false);
		rapidxml::xml_attribute<>* attrTileWidth = tilesetNode->first_attribute("tilewidth", 0, false);
		rapidxml::xml_attribute<>* attrTileHeight = tilesetNode->first_attribute("tileheight", 0, false);

		tileset.firstGID = (unsigned int)strtol(attrFirstGID->value(), 0, 10);
		tileset.name = attrName->value();
		tileset.tileWidth = (unsigned int)strtol(attrTileWidth->value(), 0, 10);
		tileset.tileHeight = (unsigned int)strtol(attrTileHeight->value(), 0, 10);


		// Get the image node and the attributes.
		rapidxml::xml_node<>* imageNode = tilesetNode->first_node("image", 0, false);
		rapidxml::xml_attribute<>* attrSource = imageNode->first_attribute("source", 0, false);

		// Load the texture.
		tileset.tex.loadFromFile(attrSource->value());

		// Add the tileset to the vector.
		tilesets.push_back(tileset);

		// Move on to the next node (if any).
		tilesetNode = tilesetNode->next_sibling();
	}


	////////////////////
	// Layers
	////////////////////
	rapidxml::xml_node<>* layerNode = mapNode->first_node("layer", 0, false);

	while(layerNode != 0)
	{
		// Get the layer attributes.
		rapidxml::xml_attribute<>* attrName = layerNode->first_attribute("name", 0, false);
		rapidxml::xml_attribute<>* attrWidth = layerNode->first_attribute("width", 0, false);
		rapidxml::xml_attribute<>* attrHeight = layerNode->first_attribute("height", 0, false);

		unsigned int layerWidth = (unsigned int)strtol(attrWidth->value(), 0, 10);
		unsigned int layerHeight = (unsigned int)strtol(attrHeight->value(), 0, 10);

		Layer layer(attrName->value(), layerWidth, layerHeight);

		// Read the data section and all the tiles.
		rapidxml::xml_node<>* dataNode = layerNode->first_node("data", 0, false);
		rapidxml::xml_node<>* tileNode = dataNode->first_node("tile", 0, false);

		while(tileNode != 0)
		{
			Tile tile;

			// Get the Global ID attribute.
			rapidxml::xml_attribute<>* attrGID = tileNode->first_attribute("gid", 0, false);
			tile.gid = (unsigned int)strtol(attrGID->value(), 0, 10);

			// Add the tile to the layer.
			layer.tiles.push_back(tile);

			// Get the next tile node (if any).
			tileNode = tileNode->next_sibling();
		}

		// Add the layer to the vector.
		layers.push_back(layer);

		// Get the next layer node (if any).
		layerNode = layerNode->next_sibling();
	}
}

Map::~Map()
{
}

void Map::Draw()
{
	
}

void Map::DrawLayer(int index)
{
}