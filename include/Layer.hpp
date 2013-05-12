#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

#include <Tile.hpp>
#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

class Layer
{
public:
	Layer(const std::string inName, int inWidth, int inHeight)
		: name(inName), width(inWidth), height(inHeight)
	{
	}

	const std::string& GetName() const
	{
		return name;
	}

	const int GetWidth() const
	{
		return width;
	}

	const int GetHeight() const
	{
		return height;
	}

	void UpdateVBO()
	{
		// Clear the VBO.
		vbo.Clear();

		// Make the vertices for each tile.
		for(int i = 0; i < tiles.size(); i++)
		{
			//Vertex v1;
			//v1.pos = Vector3(tiles[i]
		}

		//vbo.SetData(
	}

	std::vector<Tile> tiles;
private:
	std::string name;
	unsigned int width, height;

	VertexBufferObject vbo;
	IndexBufferObject ibo;
};

#endif