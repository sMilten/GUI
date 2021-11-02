#include "InputHandlerPlayState.h"


InputHandlerPlayState::InputHandlerPlayState(sf::RenderWindow& initWindow) :
	InputHandler(initWindow)
{}

void InputHandlerPlayState::setActiveGameViewArea(sf::FloatRect const initArea)
{
	activeGameViewArea = initArea;
}

void InputHandlerPlayState::setGameMouseViewCommand(std::shared_ptr<ICommand> initCommand)
{
	assert(initCommand != nullptr);
	gameMouseViewCommand = initCommand;
}

bool InputHandlerPlayState::handelButtonEvents()
{
	if (!InputHandler::handelButtonEvents())
	{
		if (activeGameViewArea.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(windowRef))))
		{
			gameMouseViewCommand->execute();
			return true;
		}
	}
	return false;
}

void InputHandlerPlayState::handleButtonsHovering()
{
	InputHandler::handleButtonsHovering();
	//if (activeGameViewArea.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(windowRef))))
	//{
	//	std::cout << "Im Window" << std::endl;
	//}
}