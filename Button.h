#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ICommand.h"

class Button
{
public:
	Button(sf::Vector2f initPosition);
	virtual ~Button();
	const bool getHoverBool() const;
	const sf::FloatRect& getFloatRect() const;
	virtual void changeFocus() {};
	virtual void draw(sf::RenderWindow& window) {};
	virtual void update(sf::Time dt) {};

protected:

	void setCollisionRectangle(const sf::FloatRect& newRectangle);

	sf::Vector2f getButtonCenter() const;

	inline void toggleHoverOverFlag() {
		mouseHoverOver = !mouseHoverOver;
	}

private:
	sf::FloatRect collisionRectangle;
	bool mouseHoverOver;
	sf::Vector2f buttonCenter;
};

