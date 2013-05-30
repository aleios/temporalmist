#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <regex>
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <zlib.h>
#include "base64.h"

unsigned int mapWidth, mapHeight, tileWidth, tileHeight;
int totalCols = 0, totalRows = 0;

struct Tileset
{
	std::string name;
	int gidstart;
	int gidend;
};

struct ControlTile
{
	int id;
	int row, col;
};

std::string CompressLayer(std::string layerData)
{
	// Deflate to a gzip format.
	uLongf bufferSize = mapWidth * mapHeight * 4;
	int ret;
	z_stream strm;
	char* out = new char[bufferSize];
	std::ostringstream oss;

	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);

	if(ret != Z_OK)
	{
		delete[] out;
		return "";
	}

	do
	{
		strm.avail_in = layerData.size();
		strm.next_in = (Bytef*)layerData.c_str();

		strm.avail_out = bufferSize;
		strm.next_out = (Bytef*)out;
		ret = deflate(&strm, Z_FINISH);

		if(ret == Z_STREAM_ERROR)
		{
			delete[] out;
			return "";
		}

		size_t have = bufferSize - strm.avail_out;
		oss.write((const char*)out, have);

	} while(strm.avail_out == 0);

	deflateEnd(&strm);
	std::string compressedString(oss.str());
	delete[] out;

	// Encode into base 64.
	compressedString = base64_encode((unsigned char*)compressedString.c_str(), compressedString.size());

	// Return the compressed encoded string.
	return compressedString;
}

void LoadTilesets(rapidxml::xml_node<>* mapNode, std::vector<Tileset>& tilesets)
{
	// Run over each tileset and shove their start and end values into the vector.
	rapidxml::xml_node<>* tilesetNode = mapNode->first_node("tileset", 0, false);

	while(tilesetNode != 0)
	{
		// Get the size of each tile.
		rapidxml::xml_attribute<>* attrGID = tilesetNode->first_attribute("firstgid", 0, false);
		rapidxml::xml_attribute<>* attrName = tilesetNode->first_attribute("name", 0, false);
		rapidxml::xml_attribute<>* attrTilewidth = tilesetNode->first_attribute("tilewidth", 0, false);
		rapidxml::xml_attribute<>* attrTileheight = tilesetNode->first_attribute("tilewidth", 0, false);

		int firstGID = (int)strtol(attrGID->value(), 0, 10);
		int tileWidth = (int)strtol(attrTilewidth->value(), 0, 10);
		int tileHeight = (int)strtol(attrTileheight->value(), 0, 10);

		// Get the size of the tilesheet.
		rapidxml::xml_node<>* imageNode = tilesetNode->first_node("image", 0, false);

		rapidxml::xml_attribute<>* attrWidth = imageNode->first_attribute("width", 0, false);
		rapidxml::xml_attribute<>* attrHeight = imageNode->first_attribute("height", 0, false);

		int width = (int)strtol(attrWidth->value(), 0, 10);
		int height = (int)strtol(attrHeight->value(), 0, 10);

		// Calculate the number of tiles in the set.
		int cols = (width / tileWidth);
		int rows = (height / tileHeight);
		int total = cols * rows;

		// Add the tileset to the vector.
		Tileset tileset;
		tileset.name = attrName->value();
		tileset.gidstart = firstGID;
		tileset.gidend = (firstGID + total) - 1;

		tilesets.push_back(tileset);

		// Get our next node.
		tilesetNode = tilesetNode->next_sibling("tileset", 0, false);
	}
}

unsigned int GetTilesetID(std::vector<Tileset>& tilesets, unsigned int gid)
{
	if(gid == 0)
		return 0;

	for(int i = 0; i < tilesets.size(); i++)
	{
		Tileset tileset = tilesets[i];

		if(gid >= tileset.gidstart && gid <= tileset.gidend)
			return i + 1;
	}

	return 0;
}

char* int2char(rapidxml::xml_document<>* doc, int value) 
{
    char tmpval[64];
    sprintf(tmpval,"%i",value);
    return doc->allocate_string(tmpval);
}

std::string StringToLower(const std::string& str)
{
	std::string tmp = str;
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	return tmp;
}

rapidxml::xml_node<>* HandleControlLayer(rapidxml::xml_node<>* layerNode, const std::vector<Tileset>& tilesets)
{
	rapidxml::xml_node<>* dataNode = layerNode->first_node("data", 0, false);

	// Find our control layers tileset ids.
	int sid = 0, eid = 0, numid = 0;
	for(int i = 0; i < tilesets.size(); i++)
	{
		if(StringToLower(tilesets[i].name) == "control")
		{
			sid = tilesets[i].gidstart;
			eid = tilesets[i].gidend;

			numid = eid - sid;
			break;
		}
	}
	
	// Grab each tile and find out which ones are which.
	rapidxml::xml_node<>* tileNode = dataNode->first_node("tile", 0, false);
	int currentCol = 0, currentRow = 0;
	std::vector<ControlTile> controlTiles;
	while(tileNode != 0)
	{
		rapidxml::xml_attribute<>* attrGID = tileNode->first_attribute("gid", 0, false);
		unsigned int gid = (unsigned int)strtol(attrGID->value(), 0, 10);

		if(gid != 0)
		{
			ControlTile tile;
			tile.col = currentCol;
			tile.row = currentRow;
			tile.id = (((eid) * (gid - sid)) / (eid - sid));
			controlTiles.push_back(tile);
		}

		tileNode = tileNode->next_sibling("tile", 0, false);

		// Increase the counts.
		currentCol++;
		if(currentCol >= totalCols)
		{
			currentCol = 0;
			currentRow++;
		}
	}

	// Get the next sibling before we delete this node.
	rapidxml::xml_node<>* returnNode = layerNode->next_sibling("layer", 0, false);

	// Remove the control layer from the layers.
	rapidxml::xml_node<>* mapNode = layerNode->parent();
	mapNode->remove_node(layerNode);

	// Put the tiles of the control layer in their own contained set.
	rapidxml::xml_document<>* docNode = mapNode->document();

	rapidxml::xml_node<>* controlNode = docNode->allocate_node(rapidxml::node_element, "control");
	mapNode->append_node(controlNode);

	for(int i = 0; i < controlTiles.size(); i++)
	{
		rapidxml::xml_node<>* controlTileNode = docNode->allocate_node(rapidxml::node_element, "tile");
		rapidxml::xml_attribute<>* attrCol = docNode->allocate_attribute("col", int2char(docNode, controlTiles[i].col));
		rapidxml::xml_attribute<>* attrRow = docNode->allocate_attribute("row", int2char(docNode, controlTiles[i].row));
		rapidxml::xml_attribute<>* attrID = docNode->allocate_attribute("id", int2char(docNode, controlTiles[i].id));

		// Append all the nodes and attributes.
		controlTileNode->append_attribute(attrCol);
		controlTileNode->append_attribute(attrRow);
		controlTileNode->append_attribute(attrID);
		controlNode->append_node(controlTileNode);
	}

	return returnNode;
}

int main(int argc, char** argv)
{
	std::string filename = "";
	if(argc > 1) // If we have a file from the commmand line.
	{
		filename = argv[1];
	}
	else // Otherwise we just ask for the file.
	{
		std::cout << "Please enter a filename: ";
		std::cin >> filename;
	}

	std::cout << "Trying to process the file: " << filename << "\n";

	// Try to open the filestream.
	std::ifstream fs(filename.c_str());

	if(fs.bad())
	{
		std::cout << "Failed to process the file: " << filename << "\n";
		return -1;
	}

	// Load the Map XML.
	std::vector<char> buffer;
	buffer.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
	buffer.push_back('\0'); // Null terminate the string.
	fs.close();

	// Process the map.
	rapidxml::xml_document<char> mapDoc;
	mapDoc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* mapNode = mapDoc.first_node("map", 0, false);

	// Load the map attributes
	rapidxml::xml_attribute<>* attrWidth = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrHeight = mapNode->first_attribute("height", 0, false);
	rapidxml::xml_attribute<>* attrTileWidth = mapNode->first_attribute("tilewidth", 0, false);
	rapidxml::xml_attribute<>* attrTileHeight = mapNode->first_attribute("tileheight", 0, false);

	mapWidth = (unsigned int)strtol(attrWidth->value(), 0, 10);
	mapHeight = (unsigned int)strtol(attrHeight->value(), 0, 10);
	tileWidth = (unsigned int)strtol(attrTileWidth->value(), 0, 10);
	tileHeight = (unsigned int)strtol(attrTileHeight->value(), 0, 10);

	totalCols = mapWidth;
	totalRows = mapHeight;

	// Load the tilesets.
	std::vector<Tileset> tilesets;
	LoadTilesets(mapNode, tilesets);

	// Run over each layer and compress them.
	rapidxml::xml_node<>* layerNode = mapNode->first_node("layer", 0, false);
	bool gotControl = false;
	while(layerNode != 0)
	{
		rapidxml::xml_attribute<>* attrName = layerNode->first_attribute("name", 0, false);
		
		// If this is the control layer.
		if(gotControl == false && StringToLower(attrName->value()) == "control")
		{
			layerNode = HandleControlLayer(layerNode, tilesets);
			gotControl = true;
		}
		else // Otherwise load it like a normal layer.
		{
			// Load the data node.
			rapidxml::xml_node<>* dataNode = layerNode->first_node("data", 0, false);

			// Loop through each tile and give it the proper parameters.
			rapidxml::xml_node<>* tileNode = dataNode->first_node("tile", 0, false);

			std::vector<rapidxml::xml_node<>*> removeNodes;
			int currentCol = 0, currentRow = 0;
			while(tileNode != 0)
			{
				// Get our tile GID.
				rapidxml::xml_attribute<>* attrGID = tileNode->first_attribute("gid", 0, false);
				unsigned int gid = (unsigned int)strtol(attrGID->value(), 0, 10);

				// If our GID == 0 then we wan to remove it.
				if(gid == 0)
				{
					removeNodes.push_back(tileNode);
				}
				else
				{
					// Modify the tile node to have an attribute describing which tileset it uses.
					char* tilesetID = int2char(&mapDoc, GetTilesetID(tilesets, gid));
					rapidxml::xml_attribute<>* attrTilesetID = mapDoc.allocate_attribute("tileset", tilesetID, 0, 0);

					// Set the col and row to the current col and row.
					char* tileCol = int2char(&mapDoc, currentCol);
					char* tileRow = int2char(&mapDoc, currentRow);
					rapidxml::xml_attribute<>* attrCol = mapDoc.allocate_attribute("col", tileCol, 0, 0);
					rapidxml::xml_attribute<>* attrRow = mapDoc.allocate_attribute("row", tileRow, 0, 0);

					// Append the attribute on to the node.
					tileNode->append_attribute(attrTilesetID);
					tileNode->append_attribute(attrCol);
					tileNode->append_attribute(attrRow);
				}

				// Get our next tile node.
				tileNode = tileNode->next_sibling("tile", 0, false);

				// Increase the counts.
				currentCol++;
				if(currentCol >= totalCols)
				{
					currentCol = 0;
					currentRow++;
				}
			}

			// Remove the useless nodes where their GID == 0
			for(int i = 0; i < removeNodes.size(); i++)
			{
				dataNode->remove_node(removeNodes[i]);
			}

			// Get our uncompressed data and remove unneeded items.
			std::ostringstream oss;
			oss << (*dataNode);
		
			// Find the unwated <data> tags.
			std::string uncompressed = oss.str();
			std::regex e("<\/?!?(data)[^>]*>");
			uncompressed = std::regex_replace(uncompressed, e, "");

			// Start compression of the data.
			std::string compressed = CompressLayer(uncompressed);
			compressed.push_back('\0');

			// Replace the nodes with their compressed form.
			dataNode->remove_all_nodes();
			char* cStr = mapDoc.allocate_string(compressed.c_str(), compressed.size());
			dataNode->value(cStr);

			// Move to the next layer for processing.
			layerNode = layerNode->next_sibling("layer", 0, false);
		}
	}
	
	// Write the new map to file.
	std::ofstream ofs(filename);
	ofs << mapDoc;
	ofs.close();
	mapDoc.clear();

	// Wait for user input.
	std::cout << "Success: Map converted.\n";
	std::cin.sync();
	std::cin.get();

	return 0;
}