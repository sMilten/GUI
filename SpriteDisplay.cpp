#include "SpriteDisplay.h"


void SpriteDisplay::addSprite(sf::Sprite newSprite)
{
	spritesToDisplay.push_back(newSprite);
}

void SpriteDisplay::draw(sf::RenderWindow& windowRef) const
{
	for (auto it : spritesToDisplay)
	{
		windowRef.draw(it);
	}
}