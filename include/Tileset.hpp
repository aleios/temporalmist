#ifndef TILESET_HPP
#define TILESET_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <Vector2.hpp>

class Tileset
{
public:
	unsigned int firstGID, lastGID;
	std::string name;
	unsigned int tileWidth, tileHeight;
	sf::Texture tex;

	Vector2 GetTileLocation(unsigned int gid)
	{
		if(gid > lastGID || gid < firstGID)
			return Vector2(-1, -1);

		// Find our amount of indices.
		unsigned int numIDS = lastGID - firstGID;

		// Find the normalized index of the TileID.
		unsigned int tID = (((numIDS) * (gid - firstGID)) / (lastGID - firstGID));

		// Find our total rows and total columns.
		int totalCols = tex.getSize().x / tileWidth;
		int totalRows = tex.getSize().y / tileHeight;

		// Find our row and column.
		unsigned int xid = tID % totalCols;
		unsigned int yid = tID / totalCols;

		return Vector2(xid, yid);
	}
};

#endif