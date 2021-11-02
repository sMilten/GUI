#pragma once
#include "GameState.h"
#include "ResourceHolder.h"
#include "StateHandler.h"

class MainMenuState : public GameState
{

public:
	MainMenuState(StateHandler& initStateHandler, CoreResourceHolder& coreResources);
	void update(sf::Time dt) override;
	void draw(sf::RenderWindow& window) override;

private:

	void setupUserInterfaceMaps() override;
	void doActionsBeforeEnd(const sf::String& nextState) override;

	void setStandardUI();
	void setStandardNormalsButtons();
	void setStandardTextBox();

	void setOptionUI();
	void setOptionButtons();

	void setStandardText();
	int sec;
	int min;
	int hour;
	sf::Time elapsedTimeForClock;

	StateHandler& stateHandler;
};

