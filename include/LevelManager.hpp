#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <vector>
#include <string>

#include <Map.hpp>

class LevelManager
{
public:
	static LevelManager* GetInstance()
	{
		if(instance == 0)
			instance = new LevelManager();
		return instance;
	}

	void LoadLevel(const std::string& inFilename)
	{
		maps.push_back(inFilename);
	}

	void SetLevel(int inIndex)
	{
		if(inIndex >= 0 && inIndex < maps.size())
		{
			currentLevel = inIndex;
			currentMap.Load(maps[currentLevel]);
		}
	}

	void nextLevel()
	{
		if(currentLevel < (maps.size() - 1))
			currentLevel++;

		currentMap.Load(maps[currentLevel]);
	}

	void prevLevel()
	{
		if(currentLevel > 0)
			currentLevel--;

		currentMap.Load(maps[currentLevel]);
	}

	unsigned int GetCurrentLevel() const
	{
		return currentLevel;
	}

	unsigned int GetNumMaps() const
	{
		return maps.size();
	}

	Map& GetCurrentMap()
	{
		return currentMap;
	}
private:
	std::vector<std::string> maps;
	Map currentMap;
	unsigned int currentLevel;

	LevelManager()
	{

	}

	static LevelManager* instance;
};

#endif