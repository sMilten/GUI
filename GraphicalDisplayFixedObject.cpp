#include "GraphicalDisplayFixedObject.h"
#include <cassert>

template<typename drawableObj>
GraphicalDisplayFixedObject<typename drawableObj>::GraphicalDisplayFixedObject(formatting initAlignment, sf::Vector2f initPos, drawableObj initObj) :
	GraphicalDisplayObject{ initAlignment },
	displayableObj{ initObj }
{

	if (initAlignment == formatting::MiddleCenter)
	{
		sf::FloatRect spriteEdges{ displayableObj.getLocalBounds() };
		displayableObj.setOrigin(sf::Vector2f{ spriteEdges.width / 2, 0 });
	}
	else if (initAlignment == formatting::TopRight)
	{
		sf::FloatRect spriteEdges{ displayableObj.getLocalBounds() };
		displayableObj.setOrigin(sf::Vector2f{ spriteEdges.width, 0 });
	}
	// formatting::TopLight = default
	displayableObj.setPosition(initPos);
}

template<typename drawableObj>
void GraphicalDisplayFixedObject<typename drawableObj>::draw(sf::RenderWindow& window) const
{
	window.draw(displayableObj);
}

template<typename drawableObj>
float GraphicalDisplayFixedObject<typename drawableObj>::getWidth() const
{
	return displayableObj.getLocalBounds().width;
}
