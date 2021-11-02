#pragma once
#include <SFML/Graphics.hpp>

class MouseSprite final
{
public:
	MouseSprite(const sf::RenderWindow& initWindow, sf::Vector2i initFrameSize);
	~MouseSprite();

	void updatePosition(const sf::Time dt);
	void draw(sf::RenderWindow& window);
	void setAnimation(const sf::Texture& initMouseTexture, const int initFrameNumber, const sf::Time initFrameLength);

private:
	static int objCounter;

	const sf::RenderWindow& window;

	sf::Sprite mouseSprite;
	sf::Vector2i spriteSize;
	sf::IntRect moveableSpriteRect;

	int maxFrames;
	int frameCounter;
	sf::Time frameTimeLenght;
	sf::Time elapsedTime;
};

