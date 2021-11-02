#pragma once
#include "GraphicalDisplayObject.h"

template<typename drawableObj>
class GraphicalDisplayFixedObject : public GraphicalDisplayObject
{
public:
	GraphicalDisplayFixedObject(formatting initAlignment, sf::Vector2f initPos, drawableObj initObj);
	void draw(sf::RenderWindow& window) const override;
	float getWidth() const override;

private:
	drawableObj displayableObj;

};