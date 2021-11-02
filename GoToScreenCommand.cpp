#include "GoToScreenCommand.h"

GoToScreenCommand::GoToScreenCommand(sf::String initDestStateName, GameState& initGameState) :
	gameStateToEnd{ initGameState },
	destinationStateName{ initDestStateName }
{}

void GoToScreenCommand::execute()
{
	gameStateToEnd.bindEndFkr(destinationStateName, *this);
}