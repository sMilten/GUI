#include "ToggleUIVisibilityCommand.h"


ToggleUIVisibilityCommand::ToggleUIVisibilityCommand(sf::String initUIName, StateInterfaceHolder& initUIHolder) :
	uiToToogle{ initUIName },
	uiHolder{ initUIHolder }
{}

void ToggleUIVisibilityCommand::execute()
{
	if (uiHolder.getUIVisibility(uiToToogle) == StateInterfaceHolder::uiState::show)
	{
		uiHolder.changeUIState(uiToToogle, StateInterfaceHolder::uiState::hide);
	}
		
	else
	{
		uiHolder.changeUIState(uiToToogle, StateInterfaceHolder::uiState::show);
	}
		
}