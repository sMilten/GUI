#pragma once
#include "Button.h"
#include "ICommand.h"

class HoverButton : public Button
{
public:
	HoverButton(sf::FloatRect collidingRect, std::unique_ptr<ICommand> icPtr);
	void changeFocus() override;

private:
	std::unique_ptr<ICommand> executeWhenHoverOver;
};

