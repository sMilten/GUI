#pragma once
#include <SFML/Graphics.hpp>
#include "StateInterfaceHolder.h"
#include "ICommand.h"
#include "UserInterface.h"
#include "Button.h"
#include "CursorV2.h"
#include <functional>

class InputHandler
{

public:
	InputHandler(sf::RenderWindow& initWindow);
	virtual ~InputHandler();
	void handleInput();

	void setKeyEvent(StateInterfaceHolder::enumKeyMap* const initKeys, StateInterfaceHolder::enumCommandMap* const initCommands);
	void setKeyRealtime(StateInterfaceHolder::enumKeyMap* const initKeys, StateInterfaceHolder::enumCommandMap* const initCommands);
	void setUIMapForMouseClicks(StateInterfaceHolder::uiMap* const initUIs);
	void setTextBoxes(StateInterfaceHolder::textBoxMap* const setActiveTextBoxes);
	void setDefaultKeyboardHandling();

protected:

	void handleEventInput();
	void handleKeyboardEvents(sf::Event& keyboardEvent);
	void handleTextEnterEvents(sf::Event& keyboardEvent);
	void handleArrowKeysInTextMode(sf::Event& keyboardEvent);
	virtual bool handelButtonEvents();

	void handleRealtimeInput();
	void handleKeyboardRealtime();
	virtual void handleButtonsHovering();
	void setTextEnterHandling();

	sf::RenderWindow& windowRef;
	bool textEnterMode;
	TextBox* selectedTextBox;
	CursorV2 cursor;

	StateInterfaceHolder::enumKeyMap* eventKeys;
	StateInterfaceHolder::enumCommandMap* eventCommands;
	StateInterfaceHolder::enumKeyMap* realtimeKeys;
	StateInterfaceHolder::enumCommandMap* realtimeCommands;
	StateInterfaceHolder::uiMap* userInterfaceMaps;
	StateInterfaceHolder::textBoxMap* activeTextBoxes;

	std::function<void(sf::Event&)> currentKeyboardFctEvents;
	std::function<void(void)> currentKeyboardFctRealtime;
};