#include "CloseWindowCommand.h"

CloseWindowCommand::CloseWindowCommand(sf::RenderWindow& initWindowRef) :
	window{ initWindowRef }
{}

void CloseWindowCommand::execute()
{
	window.close();
}