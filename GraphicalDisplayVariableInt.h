#pragma once
#include "GraphicalDisplayObject.h"

class GraphicalDisplayVariableInt : public GraphicalDisplayObject
{
public:
	GraphicalDisplayVariableInt(formatting initAlignment, sf::Vector2f initPos, sf::Text initText, int& initRef, bool clockMode = false);
	void draw(sf::RenderWindow& window) const override;
	float getWidth() const override;

	void update();

private:
	sf::Text displayValue;
	int& value;
	bool cMode;
};

