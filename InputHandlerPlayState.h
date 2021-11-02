#pragma once
#include "InputHandler.h"

class InputHandlerPlayState final: public InputHandler
{
public:
	InputHandlerPlayState(sf::RenderWindow& initWindow);

	void setActiveGameViewArea(sf::FloatRect const initArea);
	void setGameMouseViewCommand(std::shared_ptr<ICommand> initCommand);

private:
	bool handelButtonEvents() override;
	void handleButtonsHovering() override;

	sf::FloatRect activeGameViewArea; // Realtime Handling is deactived
	std::shared_ptr<ICommand> gameMouseViewCommand;
};

