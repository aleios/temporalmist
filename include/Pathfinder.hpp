#pragma once
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <vector>
#include <queue>
#include <thread>
#include <mutex>

#include <Path.hpp>

class PathRequest
{
public:
	PathNode start, end;
	std::vector<PathNode> path;
	int rid;
};

class Pathfinder
{
public:
	Pathfinder(unsigned int maxThreads);
	~Pathfinder();

	int QueueRequest(PathNode start, PathNode end);

	void Update();

private:
	std::queue<PathRequest> reqQueue;
	std::vector<PathRequest> finList;

	std::vector<std::thread> reqThreads;
	std::mutex pathMutex;

	unsigned int threadLimit, usedThreads;

	void PathThread();

	std::vector<PathNode> CalcPath(PathNode start, PathNode end);
	float CalcHeuristic(PathNode currentNode, PathNode endNode);
};

#endif