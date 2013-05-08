#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include <vector>
#include <GameState.hpp>
#include <GameSettings.hpp>
#include <SFML/Window/Event.hpp>

class StateManager
{
public:
	StateManager(const GameSettings& inSettings);
	~StateManager();

	void OnEvent(const sf::Event& ev);
	void Update(unsigned int timestep);
	void Draw(float delta);

	void AddState(GameState* inState);

	const int GetStateCount() const
	{
		return states.size();
	}
private:
	std::vector<GameState*> states;
	GameSettings settings;
};

#endif