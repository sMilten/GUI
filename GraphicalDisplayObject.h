#pragma once
#include <SFML/Graphics.hpp>

class GraphicalDisplayObject
{

public:
	enum class formatting {
		TopLeft,
		MiddleCenter,
		TopRight
	};
	GraphicalDisplayObject(formatting initAlignment);
	virtual ~GraphicalDisplayObject();
	virtual void draw(sf::RenderWindow& window) const {};
	virtual float getWidth() const { return 0;  };
	inline formatting getAlignment() {
		return alignment;
	}

private:
	formatting alignment;

};

