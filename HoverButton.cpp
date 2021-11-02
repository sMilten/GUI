#include "HoverButton.h"

HoverButton::HoverButton(sf::FloatRect collidingRect, std::unique_ptr<ICommand> icPtr) :
	Button{ sf::Vector2f{ 0,0 } },
	executeWhenHoverOver{ std::move(icPtr) }
{
	setCollisionRectangle(collidingRect);
}

void HoverButton::changeFocus()
{
	executeWhenHoverOver->execute();
}