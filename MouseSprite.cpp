#include "MouseSprite.h"
#include <cassert>

int MouseSprite::objCounter = 0;

MouseSprite::MouseSprite(
	const sf::RenderWindow& initWindow, sf::Vector2i initFrameSize) :
	window{ initWindow },
	spriteSize{ initFrameSize },
	moveableSpriteRect{ 0,0, initFrameSize.x, initFrameSize.y },
	frameCounter{ 0 },
	elapsedTime{ sf::Time::Zero },
	maxFrames{1}
{
	objCounter++;
	assert(objCounter == 1);
	mouseSprite.setTextureRect(moveableSpriteRect);
}

MouseSprite::~MouseSprite()
{
	objCounter--;
}

void MouseSprite::setAnimation(const sf::Texture& initMouseTexture, const int initFrameNumber, const sf::Time initFrameLength)
{
	mouseSprite.setTexture(initMouseTexture);
	maxFrames = initFrameNumber;
	frameTimeLenght = initFrameLength;
}

void MouseSprite::updatePosition(sf::Time dt)
{
	elapsedTime += dt;

	if (elapsedTime > frameTimeLenght)
	{

		frameCounter++;
		elapsedTime = sf::Time::Zero;
		
		if (frameCounter == maxFrames)
		{
			frameCounter = 0;
			moveableSpriteRect.left = 0;
		}
		else
		{
			moveableSpriteRect.left += spriteSize.x;
		}
		mouseSprite.setTextureRect(moveableSpriteRect);
	}
	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
	mouseSprite.setPosition(mousePosition);
}

void MouseSprite::draw(sf::RenderWindow& window)
{
	window.draw(mouseSprite);
}