#pragma once
#include <SFML/Graphics.hpp>
#include "ICommand.h"
#include "Button.h"
#include "UserInterface.h"
#include "TextBox.h"

class StateInterfaceHolder
{

public:
	enum class LinkTag
	{
		// Change Screen
		ChangeScreenToMain,
		ChangeScreenToPlay,

		// View Movement (PlayState)
		ScrollViewUp,
		ScrollViewDown,
		ScrollViewLeft,
		ScrollViewRight
	};

	enum class uiState
	{
		hide,
		show
	};

	enum class KeyBindType
	{
		Event,
		Realtime
	};
public:
	typedef std::map<StateInterfaceHolder::LinkTag, sf::Keyboard::Key> enumKeyMap;
	typedef std::map<StateInterfaceHolder::LinkTag, std::unique_ptr<ICommand>> enumCommandMap;
	typedef std::map<sf::String, std::unique_ptr<UserInterface>> uiMap;
	typedef std::map<sf::String, std::unique_ptr<TextBox>> textBoxMap;


	StateInterfaceHolder();
	StateInterfaceHolder::uiState getUIVisibility(const sf::String& uiName);
	void changeUIState(const sf::String& uiName, StateInterfaceHolder::uiState moveToState);
	void draw(sf::RenderWindow& windowRef) const;
	void update(sf::Time dt);
	void updateSpecificUI(const sf::String& nameOfUIToUpdate, const sf::String& nameOfTextToUpdate);

	void resetUI();

	void addUI(const sf::String& initUIName, StateInterfaceHolder::uiState defaultUIState, sf::FloatRect uiRectForMouseclicks = sf::FloatRect{ -10,-10,-10,-10 });
	void addButton(std::unique_ptr<Button> button, std::unique_ptr<ICommand> ic, const sf::String& uiName);
	void addSprite(const sf::String& uiName, const sf::Texture& initTexture, sf::Vector2f initPosition);
	void addGUIInformation(const sf::String& nameOfUI, const sf::String& nameOfGUIObject, sf::Vector2f initPosition);
	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode = false);
	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText);
	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite);
	void addTextBox(const sf::String& textBoxName, bool visibiltyState, std::unique_ptr<TextBox> textBox);
	void toggleTextBoxState(const sf::String& textBoxName);
	void bindKeyToCommand(KeyBindType type, LinkTag tag, sf::Keyboard::Key key, std::unique_ptr<ICommand> icPtr);

	// getter for InputHandler
	inline enumKeyMap* getKeyEventMap() {
		return &enumKeyBindingEvent;
	}
	
	inline enumCommandMap* getCommandEventMap() {
		return &enumCommandBindingEvent;
	}

	inline enumKeyMap* getKeyRealtimeMap() {
		return &enumKeyBindingRealtime;
	}

	inline enumCommandMap* getCommandRealtimeMap() {
		return &enumCommandBindingRealime;
	}

	inline uiMap* getActiveUIs() {
		return &activeUIs;
	}

	inline textBoxMap* getTextBoxes()
	{
		return &activeTextBoxes;
	}

private:

	enumKeyMap enumKeyBindingEvent;
	enumCommandMap enumCommandBindingEvent;

	enumKeyMap enumKeyBindingRealtime;
	enumCommandMap enumCommandBindingRealime;

	uiMap activeUIs;
	uiMap deactiveUIs;

	std::map<sf::String, StateInterfaceHolder::uiState> defaultUIOrder;

	textBoxMap activeTextBoxes;
	textBoxMap deactiveTextBoxes;

};