#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <map>

#include <Tile.hpp>
#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

struct LayerDesc
{
	int start;
	int end;
};

class Layer
{
public:
	Layer(const std::string inName, int inWidth, int inHeight, int inTileWidth, int inTileHeight);
	~Layer();

	const std::string& GetName() const;
	const int GetWidth() const;
	const int GetHeight() const;

	void UpdateVBO();

	void Draw();

	std::vector<Tile> tiles;
private:
	std::string name;
	unsigned int width, height, tileWidth, tileHeight;

	VertexBufferObject vbo;
	IndexBufferObject ibo;

	std::map<int, LayerDesc> layerDesc;
};

#endif