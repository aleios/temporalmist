#include <Pathfinder.hpp>

Pathfinder::Pathfinder(unsigned int maxThreads)
	: threadLimit(maxThreads), usedThreads(0)
{
}

int Pathfinder::QueueRequest(PathNode start, PathNode end)
{
	std::lock_guard<std::mutex> lck(pathMutex);

	PathRequest req;
	req.start = start;
	req.end = end;
	req.rid = reqQueue.size();

	reqQueue.push(req);

	return req.rid;
}

void Pathfinder::Update()
{
	/* If we have nothing to process then don't bother.
	if(reqQueue.size() < 1 && usedThreads < threadLimit)
		return;

	// Process requests until we have no more threads left to process on.
	while(reqQueue.size() > 0 && usedThreads < threadLimit)
	{
		// Spawn the thread.
		std::thread thr(&PathThread);
		++usedThreads;
	}*/
}

void Pathfinder::PathThread()
{
	std::lock_guard<std::mutex> lck(pathMutex);

	// Remove the topmost request from the queue.
	PathRequest req = reqQueue.front();
	reqQueue.pop();

	// Calculate the path.
	std::vector<PathNode> path;
	path = CalcPath(req.start, req.end);

	// Put the request into the finished list.
	PathRequest finReq;
	finReq.start = req.start;
	finReq.end = req.end;
	finReq.rid = req.rid;
	finReq.path = path;
	finList.push_back(finReq);

	--usedThreads;
}

std::vector<PathNode> Pathfinder::CalcPath(PathNode start, PathNode end)
{
	std::vector<PathNode> path, openList, closedList;

	// If the start is equivalent to the end or either node is stuck in a collision space then we exit the find.
	if((start.x == end.x && start.y == end.y) || start.collide || end.collide)
		return path;

	// Set the parents to null.
	start.parent = 0;
	end.parent = 0;

	// Set the current node to the start.
	PathNode* cNode = &start;

	while((cNode->x != end.x || cNode->y != end.y) && openList.size() > 0 && end.parent == 0)
	{

	}

	// Return the finished path.
	return path;
}

float Pathfinder::CalcHeuristic(PathNode currentNode, PathNode endNode)
{
	float xDist = abs(currentNode.x - endNode.x);
	float yDist = abs(currentNode.y - endNode.y);

	if(xDist > yDist)
		return 14 * yDist + 10 * (xDist - yDist);

	return 14 * xDist + 10 * (yDist - xDist);
}

/*

1. On the main thread we look for requests.
2. We keep filling requests until we hit our thread limit.
3. 

*/