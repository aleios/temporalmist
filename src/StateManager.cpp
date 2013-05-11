#include <StateManager.hpp>

StateManager::StateManager(const GameSettings& inSettings)
	: settings(inSettings)
{
}

StateManager::~StateManager()
{
	// Delete all undeleted states.
	for(auto it = states.begin(); it != states.end(); ++it)
	{
		(*it)->OnDestroy();

		delete *it;
		*it = 0;
	}

	states.clear();
}

void StateManager::OnEvent(const sf::Event& ev)
{
	if(states.size() < 1)
		return;
	states[states.size() - 1]->OnEvent(ev);
}

void StateManager::Update(unsigned int timestep)
{
	// Skip updating if we have no states to update.
	if(states.size() < 1)
		return;

	// Update the topmost state.
	states[states.size() - 1]->Update(timestep);

	// Remove the states that are flagged for removal.
	for(auto it = states.begin(); it != states.end();)
	{
		// If the state requires removal then remove it and revalidate iterator.
		if((*it)->GetDeleteFlag())
		{
			delete *it;
			*it = 0;
			it = states.erase(it);
		}
		else // Otherwise just move along.
			++it;
	}
}

void StateManager::Draw(float timestep)
{
	// If there are no states then don't bother drawing.
	if(states.size() < 1)
		return;

	// Draw the topmost state.
	GameState* activeState = states[states.size() - 1];
	activeState->Draw(timestep);

	// If the topmost state is a popup then we should draw the one below it (if it exists).
	if(activeState->IsPopup() && states.size() > 1)
	{
		states[states.size() - 2]->Draw(timestep);
	}
}

void StateManager::AddState(GameState* inState)
{
	// If the state is null then just return for now.
	if(inState == 0)
		return;
	
	// Push the state on to the top of the stack.
	states.push_back(inState);
	inState->OnCreate(settings);
}