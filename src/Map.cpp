#include <Map.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cctype>
#include <base64.h>

Map::Map()
{
}

Map::Map(const std::string& inFilename)
{
	Load(inFilename);
}

std::string Map::UncompressData(std::string data)
{
	// Clean the string from any random newlines.
	data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

	// Trim leading whitespace.
	data.erase(data.begin(), std::find_if(data.begin(), data.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));

	// Trim trailing whitespace.
	data.erase(std::find_if(data.rbegin(), data.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), data.end());
	
	// Decode base64.
	data = base64_decode(data);

	// Decompress the string.
	uLongf bufferSize = width * height * 4;

    int ret;
    z_stream strm;
    char *out = new char[bufferSize];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
	strm.next_in = (Bytef*)data.data();
    strm.avail_in = data.size();
    strm.next_out = (Bytef*)out;
    strm.avail_out = bufferSize;

    ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK)
    {
		delete[] out;
		return "";
    }

    do
    {
		ret = inflate(&strm, Z_SYNC_FLUSH);

		switch (ret)
		{
		case Z_NEED_DICT:
		case Z_STREAM_ERROR:
				ret = Z_DATA_ERROR;
		case Z_DATA_ERROR:
		case Z_MEM_ERROR:
				inflateEnd(&strm);
				delete[] out;
				return "";
		}

		if (ret != Z_STREAM_END)
		{
			out = (char *) realloc(out, bufferSize * 2);

			if (!out)
			{
				inflateEnd(&strm);
				delete[] out;
				return "";
			}

			strm.next_out = (Bytef *)(out + bufferSize);
			strm.avail_out = bufferSize;
			bufferSize *= 2;
		}
    } while (ret != Z_STREAM_END);

    if (strm.avail_in != 0)
    {
        delete[] out;
        return "";
    }

    inflateEnd(&strm);

	out[strm.total_out - 1] = '\0';

	std::string outputString(out);
	delete[] out;
    return outputString;
}

Map::~Map()
{
	for(int i = 0; i < layers.size(); i++)
	{
		delete layers[i];
	}
	layers.clear();
}

void Map::Load(const std::string& inFilename)
{
	// Load the XML from the map file.
	std::ifstream fs(inFilename.c_str());
	std::vector<char> buffer;
	buffer.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
	buffer.push_back('\0'); // Null terminate the string.
	fs.close();

	// Parse the XML.
	mapXML.parse<0>(&buffer[0]);

	// Load the map node.
	rapidxml::xml_node<>* mapNode = mapXML.first_node("map", 0, false);

	// Get the map attributes.
	rapidxml::xml_attribute<>* attrWidth = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrHeight = mapNode->first_attribute("height", 0, false);
	rapidxml::xml_attribute<>* attrTileWidth = mapNode->first_attribute("tilewidth", 0, false);
	rapidxml::xml_attribute<>* attrTileHeight = mapNode->first_attribute("tileheight", 0, false);

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

		std::string imagePath("assets/textures/" + tileset.name + ".png");

		// Load the texture.
		tileset.tex.loadFromFile(imagePath);

		// Add the tileset to the vector.
		tilesets.push_back(tileset);

		// Move on to the next node (if any).
		tilesetNode = tilesetNode->next_sibling("tileset", 0, false);
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

		Layer* layer = new Layer(attrName->value(), layerWidth, layerHeight, tileWidth, tileHeight);

		// Read the data section and all the tiles.
		rapidxml::xml_node<>* dataNode = layerNode->first_node("data", 0, false);
		std::string data = UncompressData(dataNode->value());

		// Load the tile elements into a new parsed document.
		rapidxml::xml_document<> tileDoc;
		tileDoc.parse<0>((char*)data.c_str());

		rapidxml::xml_node<>* tileNode = tileDoc.first_node("tile", 0, false);

		while(tileNode != 0)
		{
			Tile tile;

			// Get the Global ID attribute and the tileset id.
			rapidxml::xml_attribute<>* attrGID = tileNode->first_attribute("gid", 0, false);
			rapidxml::xml_attribute<>* attrTileset = tileNode->first_attribute("tileset", 0, false);
			rapidxml::xml_attribute<>* attrCol = tileNode->first_attribute("col", 0, false);
			rapidxml::xml_attribute<>* attrRow = tileNode->first_attribute("row", 0, false);
			
			tile.gid = (unsigned int)strtol(attrGID->value(), 0, 10);
			tile.tilesetID = ((int)strtol(attrTileset->value(), 0, 10)) - 1;
			tile.col = (int)strtol(attrCol->value(), 0, 10);
			tile.row = (int)strtol(attrRow->value(), 0, 10);

			// Add the tile to the layer.
			layer->tiles.push_back(tile);

			// Get the next tile node (if any).
			tileNode = tileNode->next_sibling();
		}

		// Setup the layer's VBO and IBO.
		layer->UpdateVBO();

		// Add the layer to the vector.
		layers.push_back(layer);

		// Get the next layer node (if any).
		layerNode = layerNode->next_sibling("layer", 0, false);
	}
}

void Map::Draw()
{
	for(unsigned int i = 0; i < layers.size(); i++)
	{
		DrawLayer(i);
	}
}

void Map::DrawLayer(int index)
{
	// If the layer index is above the amount of layers we have then exit.
	if(index > (layers.size() - 1))
		return;
	layers[index]->Draw();
}