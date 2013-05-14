#include <Layer.hpp>
#include <iostream>
#include <algorithm>

Layer::Layer(const std::string inName, int inWidth, int inHeight, int inTileWidth, int inTileHeight)
	: name(inName), width(inWidth), height(inHeight), tileWidth(inTileWidth), tileHeight(inTileHeight)
{
}

Layer::~Layer()
{
}

const std::string& Layer::GetName() const
{
	return name;
}

const int Layer::GetWidth() const
{
	return width;
}

const int Layer::GetHeight() const
{
	return height;
}

bool SortFunc(Tile t1, Tile t2)
{
	return (t1.tilesetID < t2.tilesetID);
}

void Layer::UpdateVBO()
{
	// Clear the VBO.
	//vbo.Clear();

	vbo.Bind();
	ibo.Bind();

	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;

	//Make the vertices for each tile.
	unsigned int currentIndex = 0;
	int currentTileset = 0;
	LayerDesc ldesc;
	ldesc.start = 0;

	int tileID = 0;

	// Sort from lowest tileset ID to highest.
	std::sort(tiles.begin(), tiles.end(), SortFunc);

	for(int i = 0; i < tiles.size(); i++)
	{
		if(tiles[i].tilesetID != currentTileset)
		{
			// Add the descriptor to the map.
			ldesc.end = currentIndex;
			layerDesc.insert(std::pair<int, LayerDesc>(currentTileset, ldesc));

			// Increase the tileset count.
			currentTileset++;
			ldesc.start = currentIndex + 1;
		}

		int xPos = tiles[i].col * tileWidth;
		int yPos = tiles[i].row * tileHeight;

		if(xPos == 0 && yPos == 32)
			std::cout << "I should be working...\n";

		float uPos = 0.0f;
		float vPos = 0.0f;

		// Add the vertices to the vertex list.
		Vertex v1;
		v1.pos = Vector3(xPos, yPos, 0);
		v1.normal = Vector3(1, 1, 1);
		// Calculate the TileCoords via the tilesheet position.
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos + tileWidth, yPos, 0);
		v1.normal = Vector3(1, 1, 1);
		// Calculate the TileCoords via the tilesheet position.
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos + tileWidth, yPos + tileHeight, 0);
		v1.normal = Vector3(1, 1, 1);
		// Calculate the TileCoords via the tilesheet position.
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos, yPos + tileHeight, 0);
		v1.normal = Vector3(1, 1, 1);
		// Calculate the TileCoords via the tilesheet position.
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		// Add the indices to the index list.
		int idx = currentIndex;
		indices.push_back(idx); indices.push_back(idx + 1); indices.push_back(idx + 2); // 0 1 2
		indices.push_back(idx); indices.push_back(idx + 3); indices.push_back(idx + 2); // 0 3 2

		/*std::cout << "Indices: [ " << idx << ", " << (idx + 1) << ", " << (idx + 2) << "]\n"
				  << "         [ " << idx << ", " << (idx + 3) << ", " << (idx + 2) << "]\n";*/

		currentIndex += 4;

		// 0 1 2
		// 0 3 2

		// 4 5 6
		// 4 7 6
		
		// 8 9 10
		// 8 11 10
	}

	std::cout << "Num Verts: " << vertices.size() << "\n";
	std::cout << "Num Indices: " << indices.size() << "\n";
	std::cout << "Tiles: " << tiles.size() << "\n";

	vbo.SetData(vertices);
	ibo.SetData(indices);

	vbo.Unbind();
	ibo.Unbind();
}

void Layer::Draw()
{
	vbo.DrawIndexed(ibo);
}