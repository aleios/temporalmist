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

unsigned int mapWidth, mapHeight;

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

	rapidxml::xml_attribute<>* attrWidth = mapNode->first_attribute("width", 0, false);
	rapidxml::xml_attribute<>* attrHeight = mapNode->first_attribute("height", 0, false);

	mapWidth = (unsigned int)strtol(attrWidth->value(), 0, 10);
	mapHeight = (unsigned int)strtol(attrHeight->value(), 0, 10);

	// Run over each layer and compress them.
	rapidxml::xml_node<>* layerNode = mapNode->first_node("layer", 0, false);

	while(layerNode != 0)
	{
		rapidxml::xml_node<>* dataNode = layerNode->first_node("data", 0, false);

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