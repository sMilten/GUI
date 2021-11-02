#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "InputHandler.h"
#include "ResourceHolder.h"
#include "CoreResourceHolder.h"

class StateHandler final
{
public:
	StateHandler(CoreResourceHolder& initResourceHolder);
	void initStates();
	void changeState(const sf::String& nextState);

	void handleInput();
	void update(sf::Time dt);
	void draw();

private:
	
	std::shared_ptr<GameState> currState;
	sf::String currStateString;
	std::map<sf::String, std::shared_ptr<GameState>> possibleStates;
	CoreResourceHolder& coreResourcesRef;
};

