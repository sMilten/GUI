#include "GraphicalDisplayVariableInt.h"
#include <sstream>

GraphicalDisplayVariableInt::GraphicalDisplayVariableInt(formatting initAlignment, sf::Vector2f initPos, sf::Text initText, int& initRef, bool clockMode) :
	GraphicalDisplayObject{ initAlignment },
	value{ initRef },
	displayValue{ initText },
	cMode{ clockMode }
{
	displayValue.setString(std::to_string(value));
	if (cMode == true && value < 10)
	{
		std::stringstream ss;
		ss << 0 << std::to_string(value);
		displayValue.setString(ss.str());
	}
		

	if (initAlignment == formatting::MiddleCenter)
	{
		sf::FloatRect spriteEdges = displayValue.getLocalBounds();
		displayValue.setOrigin(sf::Vector2f{ spriteEdges.width / 2, 0 });
	}
	else if (initAlignment == formatting::TopRight)
	{
		sf::FloatRect spriteEdges = displayValue.getLocalBounds();
		displayValue.setOrigin(sf::Vector2f{ spriteEdges.width, 0 });
	}
	// formatting::TopLight = default
	displayValue.setPosition(initPos);
}

void GraphicalDisplayVariableInt::draw(sf::RenderWindow& window) const
{
	window.draw(displayValue);
}

float GraphicalDisplayVariableInt::getWidth() const
{
	return displayValue.getLocalBounds().width;
}

void GraphicalDisplayVariableInt::update()
{

	displayValue.setString(std::to_string(value));
	if (cMode == true && value < 10)
	{
		std::stringstream ss;
		ss << 0 << std::to_string(value);
		displayValue.setString(ss.str());
	}

	if (getAlignment()== formatting::MiddleCenter)
	{
		sf::FloatRect spriteEdges{ displayValue.getLocalBounds() };
		displayValue.setOrigin(sf::Vector2f{ spriteEdges.width / 2, spriteEdges.height / 2 });
	}
	else if (getAlignment() == formatting::TopRight)
	{
		sf::FloatRect spriteEdges{ displayValue.getLocalBounds() };
		displayValue.setOrigin(sf::Vector2f{ spriteEdges.width, 0 });
	}
	// formatting::TopLight = default
}