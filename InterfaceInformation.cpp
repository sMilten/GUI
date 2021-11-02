#include "InterfaceInformation.h"

InterfaceInformation::InterfaceInformation(sf::Vector2f initStartPos) :
	currentPosition{ initStartPos }
{}

void InterfaceInformation::push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode)
{
	currentPosition.x += distanceToLastElement;
	std::shared_ptr<GraphicalDisplayVariableInt> newVar = std::make_shared<GraphicalDisplayVariableInt>(initAlignment, currentPosition, initText, initRef, clockMode);
	currentPosition.x += newVar->getWidth();
	containerToUpdate.push_back(newVar);
	displayContainer.push_back(newVar);
}

void InterfaceInformation::push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText)
{
	currentPosition.x += distanceToLastElement;
	std::shared_ptr<GraphicalDisplayFixedObject<sf::Text>> newVar = std::make_shared<GraphicalDisplayFixedObject<sf::Text>>(initAlignment, currentPosition, initText);
	currentPosition.x += newVar->getWidth();
	displayContainer.push_back(newVar);
}

void InterfaceInformation::push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite)
{
	currentPosition.x += distanceToLastElement;
	std::shared_ptr<GraphicalDisplayFixedObject<sf::Sprite>> newVar = std::make_shared<GraphicalDisplayFixedObject<sf::Sprite>>(initAlignment, currentPosition, initSprite);
	currentPosition.x += newVar->getWidth();
	displayContainer.push_back(newVar);
}

void InterfaceInformation::draw(sf::RenderWindow& window) const
{
	for (auto displayObject : displayContainer)
	{
		displayObject->draw(window);
	}
}

void InterfaceInformation::update()
{
	for (auto displayObject : containerToUpdate)
	{
		displayObject->update();
	}
}