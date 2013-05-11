#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <Color.hpp>

class Vertex
{
public:
	Vertex()
		: pos(0, 0, 0), normal(1, 1, 1), col(255, 255, 255, 255)
	{

	}

	Vertex(const Vector3& pos, const Color& col)
		: pos(pos), col(col), normal(1, 1, 1)
	{
	}

	Vector3 pos, normal;
	Vector2 texcoords;
	Color col;
};

#endif