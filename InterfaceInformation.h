#pragma once
#include "GraphicalDisplayFixedObject.h"
#include "GraphicalDisplayVariableInt.h"

class InterfaceInformation
{
public:
	InterfaceInformation(sf::Vector2f initStartPos);
	void push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode = false);
	void push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText);
	void push_back(GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite);
	void draw(sf::RenderWindow& window) const;
	void update();

private:
	sf::Vector2f currentPosition;
	std::vector<std::shared_ptr<GraphicalDisplayObject>> displayContainer;
	std::vector<std::shared_ptr<GraphicalDisplayVariableInt>> containerToUpdate;
};

