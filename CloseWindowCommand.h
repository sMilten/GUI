#pragma once
#include "ICommand.h"
#include <SFML/Graphics.hpp>

class CloseWindowCommand : public ICommand
{
public:
	CloseWindowCommand(sf::RenderWindow& initWindowRef);
	void execute() override;

private:
	sf::RenderWindow& window;

};

