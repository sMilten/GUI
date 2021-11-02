#pragma once
#include <SFML/Graphics.hpp>

class TextCursor
{
public:
	TextCursor();

	void link(unsigned int setCharSize, sf::Vector2f setPosition, sf::Color setColor = sf::Color::Black);
	void deLink();
	void newLine(bool direction, float absoluteVerticalOffset);
	void addVerticalSpace(float lengthInPx);
	void removeVerticalSpace(float lengthInPx);
	void draw(sf::RenderWindow& window) const;

private:
	sf::RectangleShape bar;
	unsigned int charSize;
	bool isLinked;
	sf::Vector2f origin;

};

