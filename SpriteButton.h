#pragma once
#include "Button.h"

class SpriteButton : public Button
{
public:
	SpriteButton(sf::Vector2f initPosition, const sf::Texture& initmainSprite);
	void changeFocus() override;
	void draw(sf::RenderWindow& window) override;
	void setSelectedSprite(const sf::Texture& initSelectedSprite);
	void setText(sf::Text initText);
	void setTextPosRelativToButtonCenter(sf::Vector2f offsetPosition);
	void setMainTextColor(sf::Color initColor);
	void setSelectedTextColor(sf::Color initColor);

private:
	sf::Sprite mainSprite;
	sf::Sprite selectedSprite;
	sf::Text buttonText;
	sf::Color mainTextColor;
	sf::Color selectedTextColor;
};

