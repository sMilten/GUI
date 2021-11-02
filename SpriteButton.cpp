#include "SpriteButton.h"

SpriteButton::SpriteButton(sf::Vector2f initPosition, const sf::Texture& initmainSprite) :
	Button{ initPosition },
	mainSprite{ initmainSprite },
	selectedSprite{ initmainSprite },
	buttonText{},
	mainTextColor { sf::Color::Black },
	selectedTextColor { sf::Color::White }
{
	mainSprite.setOrigin(mainSprite.getLocalBounds().width / 2, mainSprite.getLocalBounds().height / 2);
	mainSprite.setPosition(getButtonCenter());

	selectedSprite.setOrigin(selectedSprite.getLocalBounds().width / 2, selectedSprite.getLocalBounds().height / 2);
	selectedSprite.setPosition(getButtonCenter());

	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);
	buttonText.setPosition(getButtonCenter());

	setCollisionRectangle(mainSprite.getGlobalBounds());
}

void SpriteButton::setSelectedSprite(const sf::Texture& initSelectedSprite)
{
	selectedSprite = sf::Sprite(initSelectedSprite);
	selectedSprite.setOrigin(selectedSprite.getLocalBounds().width / 2, selectedSprite.getLocalBounds().height / 2);
	selectedSprite.setPosition(getButtonCenter());
}

void SpriteButton::setText(sf::Text initText)
{
	buttonText = sf::Text(initText);
	buttonText.setOrigin(buttonText.getLocalBounds().width / 2.f, buttonText.getLocalBounds().height / 2.f);
	buttonText.setPosition(getButtonCenter());
}

void SpriteButton::setTextPosRelativToButtonCenter(sf::Vector2f offsetPosition)
{
	buttonText.setPosition(getButtonCenter() + offsetPosition);
}

void SpriteButton::setMainTextColor(sf::Color initColor)
{
	buttonText.setFillColor(initColor);
	mainTextColor = initColor;
}

void SpriteButton::setSelectedTextColor(sf::Color initColor)
{
	selectedTextColor = initColor;
}

void SpriteButton::changeFocus()
{
	sf::Sprite tempSprite = mainSprite;
	mainSprite = selectedSprite;
	selectedSprite = tempSprite;

	sf::Color tempColor = mainTextColor;
	mainTextColor = selectedTextColor;
	selectedTextColor = tempColor;
	buttonText.setFillColor(mainTextColor);

	toggleHoverOverFlag();
}

void SpriteButton::draw(sf::RenderWindow& window)
{
	window.draw(mainSprite);
	window.draw(buttonText);
}