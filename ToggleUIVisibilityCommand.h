#pragma once
#include "ICommand.h"
#include "SFML/Graphics.hpp"
#include "StateInterfaceHolder.h"

class ToggleUIVisibilityCommand : public ICommand
{
public:
	ToggleUIVisibilityCommand(sf::String initUIName, StateInterfaceHolder& initUIHolder);
	void execute() override;

private:
	sf::String uiToToogle;
	StateInterfaceHolder& uiHolder;
};

