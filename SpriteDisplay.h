#pragma once
#include <SFML/Graphics.hpp>

class SpriteDisplay
{
public:
	void addSprite(sf::Sprite newSprite);
	void draw(sf::RenderWindow& windowRef) const;

private:
	std::vector<sf::Sprite> spritesToDisplay;
};

