#include "UserInterface.h"
#include <iostream>

UserInterface::UserInterface(sf::FloatRect mouseClickArea) :
	mouseClickArea{ mouseClickArea },
	guiInformation{}
{}

void UserInterface::addButton(std::unique_ptr<Button> addButtonToVector, std::unique_ptr<ICommand> ic)
{
	buttonMap.insert(std::make_pair(std::move(addButtonToVector), std::move(ic)));
}

void UserInterface::addSprite(const sf::Texture& initTexture, sf::Vector2f initPosition)
{
	sf::Sprite newSprite = sf::Sprite(initTexture);
	newSprite.setOrigin(newSprite.getLocalBounds().width / 2, newSprite.getLocalBounds().height / 2);
	newSprite.setPosition(initPosition);
	graphicalBackground.addSprite(newSprite);
}

void UserInterface::addGUIInformation(const sf::String& nameOfGUIObject, sf::Vector2f initPosition)
{
	auto guiWasFound = guiInformation.find(nameOfGUIObject);
	assert(guiWasFound == guiInformation.end());
	guiInformation.insert(std::make_pair(nameOfGUIObject, InterfaceInformation{ initPosition }));
}

void UserInterface::addTextToGUI(const sf::String& nameOfGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode)
{
	auto guiWasFound = guiInformation.find(nameOfGUIObject);
	assert(guiWasFound != guiInformation.end());
	guiWasFound->second.push_back(initAlignment, distanceToLastElement, initText, initRef, clockMode);
}

void UserInterface::addTextToGUI(const sf::String& nameOfGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText)
{
	auto guiWasFound = guiInformation.find(nameOfGUIObject);
	assert(guiWasFound != guiInformation.end());
	guiWasFound->second.push_back(initAlignment, distanceToLastElement, initText);
}

void UserInterface::addTextToGUI(const sf::String& nameOfGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite)
{
	auto guiWasFound = guiInformation.find(nameOfGUIObject);
	assert(guiWasFound != guiInformation.end());
	guiWasFound->second.push_back(initAlignment, distanceToLastElement, initSprite);
}

void UserInterface::update(sf::Time dt)
{
	for (auto& itVec : buttonMap)
	{
		itVec.first->update(dt);
	}
}

void UserInterface::updateVaribleText(const sf::String& nameOfTextToUpdate)
{
	auto textToUpdate = guiInformation.find(nameOfTextToUpdate);
	assert(textToUpdate != guiInformation.end());
	textToUpdate->second.update();
}

const sf::FloatRect UserInterface::getMouseClickArea() const
{
	return mouseClickArea;
}