#include <Layer.hpp>
#include <iostream>
#include <algorithm>
#include <Map.hpp>

Layer::Layer(Map* inParent, const std::string inName, int inWidth, int inHeight, int inTileWidth, int inTileHeight)
	: parent(inParent), name(inName), width(inWidth), height(inHeight), tileWidth(inTileWidth), tileHeight(inTileHeight)
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
		int xPos = tiles[i].col * tileWidth;
		int yPos = tiles[i].row * tileHeight;

		if(xPos == 0 && yPos == 32)
			std::cout << "I should be working...\n";

		Tileset& tileset = parent->tilesets[tiles[i].tilesetID];

		float uPos = 0.0f;
		float vPos = 0.0f;

		sf::Vector2u tilesetSize = tileset.tex.getSize();
		Vector2 minIndex = tileset.GetTileLocation(tiles[i].gid);
		Vector2 maxIndex = tileset.GetTileLocation(tiles[i].gid);

		Vector2 idxMin((minIndex.x * 32) / (float)tilesetSize.x,
					   (minIndex.y * 32) / (float)tilesetSize.y);

		Vector2 idxMax(((maxIndex.x * 32) + 32) / (float)tilesetSize.x,
					   ((maxIndex.y * 32) + 32) / (float)tilesetSize.y);

		// Add the vertices to the vertex list.
		Vertex v1;
		v1.pos = Vector3(xPos, yPos, 0);
		v1.normal = Vector3(1, 1, 1);
		v1.texcoords = Vector2(idxMin.x, idxMin.y);
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos + tileWidth, yPos, 0);
		v1.normal = Vector3(1, 1, 1);
		v1.texcoords = Vector2(idxMax.x, idxMin.y);
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos + tileWidth, yPos + tileHeight, 0);
		v1.normal = Vector3(1, 1, 1);
		v1.texcoords = Vector2(idxMax.x, idxMax.y);
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		v1.pos = Vector3(xPos, yPos + tileHeight, 0);
		v1.normal = Vector3(1, 1, 1);
		v1.texcoords = Vector2(idxMin.x, idxMax.y);
		v1.col = Color(255, 255, 255, 255);
		vertices.push_back(v1);

		// Add the indices to the index list.
		int idx = currentIndex;
		indices.push_back(idx); indices.push_back(idx + 1); indices.push_back(idx + 2); // 0 1 2
		indices.push_back(idx); indices.push_back(idx + 3); indices.push_back(idx + 2); // 0 3 2

		currentIndex += 4;

		if(tiles[i].tilesetID != currentTileset || i >= (tiles.size() - 1))
		{
			// Add the descriptor to the map.
			ldesc.end = indices.size();

			if(ldesc.end - ldesc.start != 0)
			{
				layerDesc.insert(std::pair<int, LayerDesc>(currentTileset, ldesc));
				ldesc.start = indices.size() + 1;
			}

			// Increase the tileset count.
			currentTileset++;
		}
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
	vbo.Bind();
	ibo.Bind();

	for(int i = 0; i < layerDesc.size(); i++)
	{
		sf::Texture::bind(&parent->tilesets[i].tex);
		glDrawElements(GL_TRIANGLES, layerDesc[i].end - layerDesc[i].start, GL_UNSIGNED_SHORT, (GLvoid*)(layerDesc[i].start * sizeof(unsigned short)));
	}

	vbo.Unbind();
}