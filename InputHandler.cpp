#include "InputHandler.h"
#include "GameState.h"
#include <cassert>
#include <iostream>

InputHandler::InputHandler(sf::RenderWindow& initWindow) :
	windowRef{initWindow},
	eventKeys{},
	eventCommands{},
	realtimeKeys{},
	realtimeCommands{},
	userInterfaceMaps{},
	activeTextBoxes{},
	textEnterMode{false},
	selectedTextBox{},
	cursor{}
{}

InputHandler::~InputHandler() {}

void InputHandler::handleInput()
{
	handleEventInput();
	handleRealtimeInput();
}

void InputHandler::setKeyEvent(StateInterfaceHolder::enumKeyMap* const initKeys, StateInterfaceHolder::enumCommandMap* const initCommands)
{
	eventKeys = initKeys;
	eventCommands = initCommands;
}

void InputHandler::setKeyRealtime(StateInterfaceHolder::enumKeyMap* const initKeys, StateInterfaceHolder::enumCommandMap* const initCommands)
{
	realtimeKeys = initKeys;
	realtimeCommands = initCommands;
}

void InputHandler::setUIMapForMouseClicks(StateInterfaceHolder::uiMap* const initUIs)
{
	userInterfaceMaps = initUIs;
}

void InputHandler::setTextBoxes(StateInterfaceHolder::textBoxMap* const setActiveTextBoxes)
{
	activeTextBoxes = setActiveTextBoxes;
}

//----------------------------------------------- Event Handling

void InputHandler::handleEventInput()
{
	sf::Event inputDeviceEvent;

	while (windowRef.pollEvent(inputDeviceEvent))
	{
		switch (inputDeviceEvent.type) {
	
		case sf::Event::Closed:
			windowRef.close();
			break;

		case sf::Event::KeyPressed:
			if (textEnterMode == false)
			{
				handleKeyboardEvents(inputDeviceEvent);
			}
			else
			{
				handleArrowKeysInTextMode(inputDeviceEvent);
			}
			break;

		case sf::Event::TextEntered:
			if(textEnterMode == true)
				handleTextEnterEvents(inputDeviceEvent);
			break;

		case sf::Event::MouseButtonReleased:
			handelButtonEvents();
			break;

		//case sf::Event::MouseLeft: "herraustaben"
			
		}	  
	}
}

void InputHandler::handleKeyboardEvents(sf::Event& keyboardEvent)
{
	for (auto enumKey : *eventKeys)
	{
		if (keyboardEvent.key.code == enumKey.second)
		{
			eventCommands->find(enumKey.first)->second->execute();
		}
	}
}

bool InputHandler::handelButtonEvents()
{
	sf::Vector2f mousePosition{ static_cast<sf::Vector2f>(sf::Mouse::getPosition(windowRef)) };

	for (auto& itUIs : *userInterfaceMaps)
	{
		if (itUIs.second->getMouseClickArea().contains(mousePosition))
		{
			for (auto& itButtons : itUIs.second->getButtons())
			{
				if (itButtons.first->getFloatRect().contains(mousePosition))
				{
					itButtons.second->execute();
					return true;
				}
			}
		}
	}
	for (auto& itTextBoxes : *activeTextBoxes)
	{
		if (itTextBoxes.second->getFloatRect().contains(mousePosition))
		{
			setTextEnterHandling();
			selectedTextBox = itTextBoxes.second.get();
			cursor.linkWordContainerViaTextBox(selectedTextBox);
			return true;
		}
		else
		{
			setDefaultKeyboardHandling();
			cursor.unlinkContainer();
		}
	}
	return false;
}

//----------------------------------------------- Realtime Handling

void InputHandler::handleRealtimeInput()
{
	if(textEnterMode == false)
		handleKeyboardRealtime();
	handleButtonsHovering();
}

void InputHandler::handleKeyboardRealtime()
{
	for (auto enumKey : *realtimeKeys)
	{
		if (sf::Keyboard::isKeyPressed(enumKey.second))
		{
			realtimeCommands->find(enumKey.first)->second->execute();
		}
	}
}

void InputHandler::handleButtonsHovering()
{
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(windowRef));
	for (auto& itUIs : *userInterfaceMaps)
	{
		for (auto& itMap : itUIs.second->getButtons())
		{
			// activate hovered over
			if (itMap.first->getHoverBool() == false && itMap.first->getFloatRect().contains(mousePosition))
			{
				itMap.first->changeFocus();
			}
			// deactivate hovered over
			else if (itMap.first->getHoverBool() == true && !itMap.first->getFloatRect().contains(mousePosition))
			{
				itMap.first->changeFocus();
			}
		}
	}
}

void InputHandler::setDefaultKeyboardHandling()
{
	textEnterMode = false;
}

void InputHandler::setTextEnterHandling()
{
	textEnterMode = true;
}

void InputHandler::handleTextEnterEvents(sf::Event& keyboardEvent)
{
	handleArrowKeysInTextMode(keyboardEvent);

	if (keyboardEvent.text.unicode == 9)
	{ }
	else if (keyboardEvent.text.unicode == 13)
	{
		selectedTextBox->newLine();
	}
	else if (keyboardEvent.text.unicode == 8)
	{
		selectedTextBox->removeCharacter();
	}
	else if (keyboardEvent.text.unicode >= 32 && keyboardEvent.text.unicode <= 126)
	{
		cursor.addChar(keyboardEvent.text.unicode);
		selectedTextBox->addUniCodeCharacter(keyboardEvent.text.unicode);
	}
}

void InputHandler::handleArrowKeysInTextMode(sf::Event& keyboardEvent)
{
	if (keyboardEvent.key.code == sf::Keyboard::Left)
	{
		cursor.moveCursorToTheLeft();
	}
	else if (keyboardEvent.key.code == sf::Keyboard::Right)
	{
		cursor.moveCursorToTheRight();
	}
}