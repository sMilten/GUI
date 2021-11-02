#pragma once
#include "ICommand.h"
#include "GameState.h"

class GoToScreenCommand : public ICommand
{
public:
	GoToScreenCommand(sf::String initDestStateName, GameState& initGameState);

	void execute() override;

private:
	GameState& gameStateToEnd;
	sf::String destinationStateName;
};

