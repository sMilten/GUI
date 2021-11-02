#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

#include "ICommand.h"
#include "ResourceHolder.h"
#include "CoreResourceHolder.h"
#include "StateInterfaceHolder.h"
#include "InputHandler.h"

class GameState
{

public:
	GameState(CoreResourceHolder& coreResources);
	virtual ~GameState();

	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderWindow& window);
	virtual void handleInput();
	virtual void setInputHandlerMaps();
	void bindEndFkr(const sf::String& nextState, ICommand& commandAsKey);

protected:

	void addButton(std::unique_ptr<Button> button, std::unique_ptr<ICommand> ic, const sf::String& uiName);

	void addUI(const sf::String& initUIName, StateInterfaceHolder::uiState defaultUIState, const sf::FloatRect& uiRectForMouseclicks);

	void addSprite(const sf::String& uiName, const sf::Texture& initTexture, sf::Vector2f initPosition);

	void addGUIInformation(const sf::String& nameOfUI, const sf::String& nameOfGUIObject, sf::Vector2f initPosition);

	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode = false);
	void updateSpecificUI(const sf::String& nameOfUIToUpdate, const sf::String& nameOfTextToUpdate);

	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText);

	void addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite);

	void addTextBox(const sf::String& textBoxName, bool visibiltyState, std::unique_ptr<TextBox> textBox);

	void toggleTextBoxState(const sf::String& textBoxName);

	void initTextObject(sf::Text& textRef, const sf::String& buttonText, int charSize, const sf::Font& buttonFont);

	StateInterfaceHolder& getInterfaceForToggleCommand();

	void interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType type, StateInterfaceHolder::LinkTag tag, sf::Keyboard::Key key, std::unique_ptr<ICommand> icPtr);

	std::unique_ptr<InputHandler> inputHandler;
	CoreResourceHolder& coreResourceRef;

private:
	void endThisState(sf::String nextState);
	virtual void doActionsBeforeEnd(const sf::String& nextState) = 0;

	virtual void setEventMaps() {};
	virtual void setRealtimeMaps() {};
	virtual void setupUserInterfaceMaps() {};
	
	std::function<void()> endStateFtr;
	StateInterfaceHolder interfaceModul;
};