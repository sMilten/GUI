#include "Button.h"

#include <iostream>
using std::endl;
using std::cout;

Button::Button(sf::Vector2f initPosition) :
	buttonCenter{ initPosition },
	mouseHoverOver{ false },
	collisionRectangle{ 0,0,0,0 }
{}

Button::~Button() {}

const bool Button::getHoverBool() const
{
	return mouseHoverOver;
}

const sf::FloatRect& Button::getFloatRect() const
{
	return collisionRectangle; 
}

void Button::setCollisionRectangle(const sf::FloatRect& newRectangle)
{
	collisionRectangle = newRectangle;
}

sf::Vector2f Button::getButtonCenter() const
{
	return buttonCenter;
}