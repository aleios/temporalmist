#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Window/Event.hpp>
#include <GameSettings.hpp>

class GameState
{
public:
	GameState(bool inPopup = false)
		: popup(inPopup), deleteFlag(false)
	{

	}
	virtual ~GameState()
	{
	}

	virtual void OnCreate(const GameSettings& inSettings) = 0;
	virtual void OnEvent(const sf::Event& ev) = 0;
	virtual void Update(unsigned int timestep) = 0;
	virtual void Draw(float delta) = 0;
	virtual void OnDestroy() = 0;

	const bool IsPopup() const
	{
		return popup;
	}
	
	void MarkForDeletion()
	{
		deleteFlag = true;
	}

	const bool GetDeleteFlag() const
	{
		return deleteFlag;
	}

private:
	bool popup, deleteFlag;
};

#endif