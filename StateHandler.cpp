#include "StateHandler.h"
#include <cassert>

#include "MainMenuState.h"
#include "PlayState.h"

StateHandler::StateHandler(CoreResourceHolder& initResourceHolder) :
	coreResourcesRef{ initResourceHolder }
{}

void StateHandler::initStates()
{
	std::shared_ptr<MainMenuState> mainMenuState = std::make_shared<MainMenuState>(*this, coreResourcesRef);
	sf::String mainMenuStateString = "MainMenu_State";

	std::shared_ptr<PlayState> playState = std::make_shared<PlayState>(*this,
		sf::FloatRect{ 128, 128, 0, 24 }, coreResourcesRef); // distance from: left, top, right, bottom
	playState->initMap(sf::Vector2f{ 32,32 }, sf::Vector2i{ 63,63 });
	playState->setScrollSpeed(sf::Vector2f{ 200, 200 });
	sf::String playStateString = "Play_State";

	currState = mainMenuState;
	currStateString = mainMenuStateString;

	mainMenuState->setInputHandlerMaps();

	possibleStates.insert(std::make_pair(mainMenuStateString, mainMenuState));
	possibleStates.insert(std::make_pair(playStateString, playState));
}

void StateHandler::changeState(const sf::String& nextState)
{
	auto foundStatePair = possibleStates.find(nextState);
	assert(foundStatePair != possibleStates.end());

	currState = foundStatePair->second;
	currStateString = nextState;

	currState->setInputHandlerMaps();
}

void StateHandler::update(sf::Time dt)
{
	currState->update(dt);
}

void StateHandler::draw()
{
	currState->draw(coreResourcesRef.getWindow());
}

void StateHandler::handleInput()
{
	currState->handleInput();
}