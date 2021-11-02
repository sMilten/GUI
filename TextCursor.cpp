#include "TextCursor.h"

TextCursor::TextCursor() :
	charSize{ 0 },
	isLinked{ false }
{}

void TextCursor::link(unsigned int setCharSize, sf::Vector2f setPosition, sf::Color setColor)
{
	origin = setPosition;
	bar.setSize(sf::Vector2f{ 1, static_cast<float>(setCharSize) });
	bar.setPosition(setPosition);
	bar.setFillColor(setColor);
	charSize = setCharSize;
	isLinked = true;
}

void TextCursor::deLink()
{
	isLinked = false;
}

void TextCursor::newLine(bool direction, float absoluteVerticalOffset)
{
	if (direction == true) // Enter also nach unten
	{
		bar.setPosition(origin.x + absoluteVerticalOffset, bar.getPosition().y + charSize * 1.2f);
	}
	else
	{
		bar.setPosition(origin.x + absoluteVerticalOffset, bar.getPosition().y - charSize * 1.2f);
	}
}

void TextCursor::addVerticalSpace(float lengthInPx)
{
	bar.setPosition(bar.getPosition().x + lengthInPx, bar.getPosition().y);
}

void TextCursor::removeVerticalSpace(float lengthInPx)
{
	bar.setPosition(bar.getPosition().x - lengthInPx, bar.getPosition().y);
}

void TextCursor::draw(sf::RenderWindow& window) const
{
	if (isLinked)
		window.draw(bar);
}