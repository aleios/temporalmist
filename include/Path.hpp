#ifndef PATH_HPP
#define PATH_HPP

#include <vector>

class PathNode
{
public:
	float x, y;

	std::vector<PathNode*> neighbors;
	PathNode* parent;

	bool collide;
};


class Path
{
public:
	Path();
private:
	std::vector<PathNode> nodes;
};

#endif