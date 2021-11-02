#pragma once
#include "Button.h"
#include "SpriteDisplay.h"
#include "ICommand.h"
#include "InterfaceInformation.h"

class UserInterface
{
public:
	UserInterface(sf::FloatRect initMouseClickArea);
	void addButton(std::unique_ptr<Button> addButtonToVector, std::unique_ptr<ICommand> ic);
	void addSprite(const sf::Texture& texture, sf::Vector2f initPosition);
	void addGUIInformation(const sf::String& nameOfGUIObject, sf::Vector2f initPosition);
	void addTextToGUI(const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode = false);
	void addTextToGUI(const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText);
	void addTextToGUI(const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite);

	void update(sf::Time dt);
	void updateVaribleText(const sf::String& nameOfTextToUpdate);

	inline const std::map<std::unique_ptr<Button>, std::unique_ptr<ICommand>>& getButtons() const
	{
		return buttonMap;
	}

	inline const std::map<sf::String, InterfaceInformation>& getText() const
	{
		return guiInformation;
	}

	inline const SpriteDisplay& getBackground() const
	{
		return graphicalBackground;
	}
	const sf::FloatRect getMouseClickArea() const;

private:
	SpriteDisplay graphicalBackground;
	std::map<std::unique_ptr<Button>, std::unique_ptr<ICommand>> buttonMap;
	std::map<sf::String, InterfaceInformation> guiInformation;
	sf::FloatRect mouseClickArea;
};
