#pragma once
#include "GameState.h"
#include "ResourceHolder.h"
#include "StateHandler.h"
#include "World.h"
#include "InputHandlerPlayState.h"
#include "ScreenScroller.h"

class PlayState final: public GameState
{
public:
	PlayState(StateHandler& initStateHandler, sf::FloatRect uiDistanceToView, CoreResourceHolder& coreResources);
	void update(sf::Time dt) override;
	void draw(sf::RenderWindow& window) override;
	void setInputHandlerMaps() override;
	void initMap(sf::Vector2f initTileSize, sf::Vector2i initTileNumber);
	void setScrollSpeed(sf::Vector2f initSpeed);
	
private:

	void doActionsBeforeEnd(const sf::String& nextState) override;
	void setRealtimeMaps() override;
	void setupUserInterfaceMaps() override;

	void setStandardUI();
	void setStandardNormalsButtons();
	void setHoverAreaButtons();

	void setOptionUI();
	void setOptionButtons();

	sf::FloatRect activeGameViewArea;
	std::shared_ptr<ICommand> gameMouseViewCommand; // init as LeftClick!

	StateHandler& stateHandler;
	ScreenScroller scroller;
	World world;
};

