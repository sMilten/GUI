#include "TextBox.h"
#include <cassert>
#include <iostream>

#define HORIZONTAL_CURSOR_OFFSET 2

TextboxData::SpecificTextBoxData::SpecificTextBoxData(sf::Vector2f initOrigin, float initTextLenghtInPx, unsigned int initNumberOfVisibleLines) :
	origin{initOrigin},
	textLenghtInPx{ initTextLenghtInPx },
	numberOfVisibleLines{ initNumberOfVisibleLines }
{}

TextboxData::GeneralTextBoxData::GeneralTextBoxData(const sf::Text& initText, sf::Vector2f initDistanceTextToInnerFrame, sf::Vector2f initFrameThickness, float initCorrectionToBottom, float initRadius) :
	text{ initText },
	distanceTextToInnerFrame{ initDistanceTextToInnerFrame },
	frameThickness{ initFrameThickness },
	correctionToBottom{ initCorrectionToBottom },
	radius{ initRadius }
{}

TextBox::TextBox(sf::Vector2f setOrigin, float setTextLenght, int initNoOfVisibleLines, const sf::Text& initText, sf::Vector2f distanceTextToInnerFrame, sf::Vector2f frameThickness, float correctionToBottom, float radius) :
	visibleShapesOfBox{},
	roundsForRoundedBox{},
	visibleText{ initText },
	textLengthInPx{ setTextLenght },
	textContent{},
	textContainer{ initText, initNoOfVisibleLines, static_cast<int>(setTextLenght) }
{
	// Test the Line!
	textForTestIntelligentLine = initText;
	textForTestIntelligentLine.setPosition(500, 800);
	textForTestIntelligentLine.setString("Intelligent Line");
	// ---- END

	visibleText.setString("");
	assert(radius >= -1);

	float totalBoxHeight = visibleText.getCharacterSize() + 2 * distanceTextToInnerFrame.y + 2 * frameThickness.y;
	float totalBoxLenght = setTextLenght + 2 * distanceTextToInnerFrame.x + 2 * frameThickness.x;
	if (initNoOfVisibleLines > 1)
	{
		totalBoxHeight += visibleText.getCharacterSize() * 1.2f * (initNoOfVisibleLines - 1);
	}
	upperLeftCornerForText = sf::Vector2f{ setOrigin.x - setTextLenght / 2.f, setOrigin.y - totalBoxHeight / 2.f + distanceTextToInnerFrame.y + frameThickness.y + correctionToBottom };
	textAndClickableArea = sf::FloatRect{ upperLeftCornerForText , sf::Vector2f{textLengthInPx, totalBoxHeight - 2 * distanceTextToInnerFrame.y - 2 * frameThickness.y} };
	visibleText.setPosition(upperLeftCornerForText);

	if (radius == -1)
	{
		testShape.setPosition(upperLeftCornerForText);
		testShape.setSize(sf::Vector2f{ textAndClickableArea.width, textAndClickableArea.height });
		testShape.setFillColor(sf::Color::Red);


		sf::RectangleShape upperRectangle{ sf::Vector2f{totalBoxLenght, frameThickness.y} };
		sf::RectangleShape lowerRectangle{ sf::Vector2f{totalBoxLenght, frameThickness.y} };
		sf::RectangleShape leftRectangle{ sf::Vector2f{frameThickness.x, totalBoxHeight} };
		sf::RectangleShape rightRectangle{ sf::Vector2f{frameThickness.x, totalBoxHeight} };
		sf::RectangleShape background{ sf::Vector2f{totalBoxLenght - 2 * frameThickness.x, totalBoxHeight - 2 * frameThickness.y} };

		upperRectangle.setOrigin(upperRectangle.getLocalBounds().width / 2.f, upperRectangle.getLocalBounds().height / 2.f);
		lowerRectangle.setOrigin(lowerRectangle.getLocalBounds().width / 2.f, lowerRectangle.getLocalBounds().height / 2.f);
		leftRectangle.setOrigin(leftRectangle.getLocalBounds().width / 2.f, leftRectangle.getLocalBounds().height / 2.f);
		rightRectangle.setOrigin(rightRectangle.getLocalBounds().width / 2.f, rightRectangle.getLocalBounds().height / 2.f);
		background.setOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);

		float yCenterOfBars = (totalBoxHeight - frameThickness.y) / 2.f;
		float xCenterOfPilars = (totalBoxLenght - frameThickness.x) / 2.f;

		upperRectangle.setPosition(setOrigin.x, setOrigin.y - yCenterOfBars);
		lowerRectangle.setPosition(setOrigin.x, setOrigin.y + yCenterOfBars);
		leftRectangle.setPosition(setOrigin.x - xCenterOfPilars, setOrigin.y);
		rightRectangle.setPosition(setOrigin.x + xCenterOfPilars, setOrigin.y);
		background.setPosition(setOrigin);

		visibleShapesOfBox.push_back(background);
		visibleShapesOfBox.push_back(upperRectangle);
		visibleShapesOfBox.push_back(lowerRectangle);
		visibleShapesOfBox.push_back(leftRectangle);
		visibleShapesOfBox.push_back(rightRectangle);

		for (auto& shapeIt : visibleShapesOfBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
		visibleShapesOfBox.begin()->setFillColor(sf::Color::White);
	}
	else
	{
		sf::RectangleShape upperRectangle{ sf::Vector2f{totalBoxLenght - radius * 2, frameThickness.y} };
		sf::RectangleShape lowerRectangle{ sf::Vector2f{totalBoxLenght - radius * 2, frameThickness.y} };
		sf::RectangleShape leftRectangle{ sf::Vector2f{frameThickness.x, totalBoxHeight - radius * 2} };
		sf::RectangleShape rightRectangle{ sf::Vector2f{frameThickness.x, totalBoxHeight - radius * 2} };
		sf::RectangleShape background{ sf::Vector2f{totalBoxLenght - 2 * frameThickness.x, totalBoxHeight - 2 * frameThickness.y} };

		upperRectangle.setOrigin(upperRectangle.getLocalBounds().width / 2.f, upperRectangle.getLocalBounds().height / 2.f);
		lowerRectangle.setOrigin(lowerRectangle.getLocalBounds().width / 2.f, lowerRectangle.getLocalBounds().height / 2.f);
		leftRectangle.setOrigin(leftRectangle.getLocalBounds().width / 2.f, leftRectangle.getLocalBounds().height / 2.f);
		rightRectangle.setOrigin(rightRectangle.getLocalBounds().width / 2.f, rightRectangle.getLocalBounds().height / 2.f);
		background.setOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);

		float yCenterOfBars = (totalBoxHeight - frameThickness.y) / 2.f;
		float xCenterOfPilars = (totalBoxLenght - frameThickness.x) / 2.f;

		upperRectangle.setPosition(setOrigin.x, setOrigin.y - yCenterOfBars);
		lowerRectangle.setPosition(setOrigin.x, setOrigin.y + yCenterOfBars);
		leftRectangle.setPosition(setOrigin.x - xCenterOfPilars, setOrigin.y);
		rightRectangle.setPosition(setOrigin.x + xCenterOfPilars, setOrigin.y);
		background.setPosition(setOrigin);

		visibleShapesOfBox.push_back(background);
		visibleShapesOfBox.push_back(upperRectangle);
		visibleShapesOfBox.push_back(lowerRectangle);
		visibleShapesOfBox.push_back(leftRectangle);
		visibleShapesOfBox.push_back(rightRectangle);

		for (auto& shapeIt : visibleShapesOfBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
		visibleShapesOfBox.begin()->setFillColor(sf::Color::White);

		sf::CircleShape upperLeft{ radius };
		sf::CircleShape upperRight{ radius };
		sf::CircleShape lowerLeft{ radius };
		sf::CircleShape lowerRight{ radius };

		upperLeft.setOrigin(radius, radius);
		upperRight.setOrigin(radius, radius);
		lowerLeft.setOrigin(radius, radius);
		lowerRight.setOrigin(radius, radius);

		upperLeft.setPosition(setOrigin.x - totalBoxLenght / 2.f + radius, setOrigin.y - totalBoxHeight / 2.f + radius);
		upperRight.setPosition(setOrigin.x + totalBoxLenght / 2.f - radius, setOrigin.y - totalBoxHeight / 2.f + radius);
		lowerLeft.setPosition(setOrigin.x - totalBoxLenght / 2.f + radius, setOrigin.y + totalBoxHeight / 2.f - radius);
		lowerRight.setPosition(setOrigin.x + totalBoxLenght / 2.f - radius, setOrigin.y + totalBoxHeight / 2.f - radius);

		roundsForRoundedBox.push_back(upperLeft);
		roundsForRoundedBox.push_back(upperRight);
		roundsForRoundedBox.push_back(lowerLeft);
		roundsForRoundedBox.push_back(lowerRight);

		for (auto& shapeIt : roundsForRoundedBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
	}
}

TextBox::TextBox(TextboxData::GeneralTextBoxData generalData, TextboxData::SpecificTextBoxData specificData) :
	visibleShapesOfBox{},
	roundsForRoundedBox{},
	visibleText{ generalData.text },
	textLengthInPx{ specificData.textLenghtInPx },
	textContent{},
	textContainer{ generalData.text, specificData.numberOfVisibleLines, static_cast<int>(specificData.textLenghtInPx) }
{
	// Test the Line!
	textForTestIntelligentLine = generalData.text;
	textForTestIntelligentLine.setPosition(500, 800);
	textForTestIntelligentLine.setString("Intelligent Line");
	// ---- END

	visibleText.setString("");
	assert(generalData.radius >= -1);

	float totalBoxHeight = visibleText.getCharacterSize() + 2 * generalData.distanceTextToInnerFrame.y + 2 * generalData.frameThickness.y;
	float totalBoxLenght = textLengthInPx + 2 * generalData.distanceTextToInnerFrame.x + 2 * generalData.frameThickness.x;
	if (specificData.numberOfVisibleLines > 1)
	{
		totalBoxHeight += visibleText.getCharacterSize() * 1.2f * (specificData.numberOfVisibleLines - 1);
	}
	upperLeftCornerForText = sf::Vector2f{ specificData.origin.x - specificData.textLenghtInPx / 2.f,
		specificData.origin.y - totalBoxHeight / 2.f + generalData.distanceTextToInnerFrame.y + generalData.frameThickness.y + generalData.correctionToBottom };
	textAndClickableArea = sf::FloatRect{ upperLeftCornerForText , sf::Vector2f{textLengthInPx, totalBoxHeight - 2 * generalData.distanceTextToInnerFrame.y - 2 * generalData.frameThickness.y} };
	visibleText.setPosition(upperLeftCornerForText);

	if (generalData.radius == -1)
	{
		testShape.setPosition(upperLeftCornerForText);
		testShape.setSize(sf::Vector2f{ textAndClickableArea.width, textAndClickableArea.height });
		testShape.setFillColor(sf::Color::Red);


		sf::RectangleShape upperRectangle{ sf::Vector2f{totalBoxLenght, generalData.frameThickness.y} };
		sf::RectangleShape lowerRectangle{ sf::Vector2f{totalBoxLenght, generalData.frameThickness.y} };
		sf::RectangleShape leftRectangle{ sf::Vector2f{generalData.frameThickness.x, totalBoxHeight} };
		sf::RectangleShape rightRectangle{ sf::Vector2f{generalData.frameThickness.x, totalBoxHeight} };
		sf::RectangleShape background{ sf::Vector2f{totalBoxLenght - 2 * generalData.frameThickness.x, totalBoxHeight - 2 * generalData.frameThickness.y} };

		upperRectangle.setOrigin(upperRectangle.getLocalBounds().width / 2.f, upperRectangle.getLocalBounds().height / 2.f);
		lowerRectangle.setOrigin(lowerRectangle.getLocalBounds().width / 2.f, lowerRectangle.getLocalBounds().height / 2.f);
		leftRectangle.setOrigin(leftRectangle.getLocalBounds().width / 2.f, leftRectangle.getLocalBounds().height / 2.f);
		rightRectangle.setOrigin(rightRectangle.getLocalBounds().width / 2.f, rightRectangle.getLocalBounds().height / 2.f);
		background.setOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);

		float yCenterOfBars = (totalBoxHeight - generalData.frameThickness.y) / 2.f;
		float xCenterOfPilars = (totalBoxLenght - generalData.frameThickness.x) / 2.f;

		upperRectangle.setPosition(specificData.origin.x, specificData.origin.y - yCenterOfBars);
		lowerRectangle.setPosition(specificData.origin.x, specificData.origin.y + yCenterOfBars);
		leftRectangle.setPosition(specificData.origin.x - xCenterOfPilars, specificData.origin.y);
		rightRectangle.setPosition(specificData.origin.x + xCenterOfPilars, specificData.origin.y);
		background.setPosition(specificData.origin);

		visibleShapesOfBox.push_back(background);
		visibleShapesOfBox.push_back(upperRectangle);
		visibleShapesOfBox.push_back(lowerRectangle);
		visibleShapesOfBox.push_back(leftRectangle);
		visibleShapesOfBox.push_back(rightRectangle);

		for (auto& shapeIt : visibleShapesOfBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
		visibleShapesOfBox.begin()->setFillColor(sf::Color::White);
	}
	else
	{
		sf::RectangleShape upperRectangle{ sf::Vector2f{totalBoxLenght - generalData.radius * 2, generalData.frameThickness.y} };
		sf::RectangleShape lowerRectangle{ sf::Vector2f{totalBoxLenght - generalData.radius * 2, generalData.frameThickness.y} };
		sf::RectangleShape leftRectangle{ sf::Vector2f{generalData.frameThickness.x, totalBoxHeight - generalData.radius * 2} };
		sf::RectangleShape rightRectangle{ sf::Vector2f{generalData.frameThickness.x, totalBoxHeight - generalData.radius * 2} };
		sf::RectangleShape background{ sf::Vector2f{totalBoxLenght - 2 * generalData.frameThickness.x, totalBoxHeight - 2 * generalData.frameThickness.y} };

		upperRectangle.setOrigin(upperRectangle.getLocalBounds().width / 2.f, upperRectangle.getLocalBounds().height / 2.f);
		lowerRectangle.setOrigin(lowerRectangle.getLocalBounds().width / 2.f, lowerRectangle.getLocalBounds().height / 2.f);
		leftRectangle.setOrigin(leftRectangle.getLocalBounds().width / 2.f, leftRectangle.getLocalBounds().height / 2.f);
		rightRectangle.setOrigin(rightRectangle.getLocalBounds().width / 2.f, rightRectangle.getLocalBounds().height / 2.f);
		background.setOrigin(background.getLocalBounds().width / 2.f, background.getLocalBounds().height / 2.f);

		float yCenterOfBars = (totalBoxHeight - generalData.frameThickness.y) / 2.f;
		float xCenterOfPilars = (totalBoxLenght - generalData.frameThickness.x) / 2.f;

		upperRectangle.setPosition(specificData.origin.x, specificData.origin.y - yCenterOfBars);
		lowerRectangle.setPosition(specificData.origin.x, specificData.origin.y + yCenterOfBars);
		leftRectangle.setPosition(specificData.origin.x - xCenterOfPilars, specificData.origin.y);
		rightRectangle.setPosition(specificData.origin.x + xCenterOfPilars, specificData.origin.y);
		background.setPosition(specificData.origin);

		visibleShapesOfBox.push_back(background);
		visibleShapesOfBox.push_back(upperRectangle);
		visibleShapesOfBox.push_back(lowerRectangle);
		visibleShapesOfBox.push_back(leftRectangle);
		visibleShapesOfBox.push_back(rightRectangle);

		for (auto& shapeIt : visibleShapesOfBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
		visibleShapesOfBox.begin()->setFillColor(sf::Color::White);

		sf::CircleShape upperLeft{ generalData.radius };
		sf::CircleShape upperRight{ generalData.radius };
		sf::CircleShape lowerLeft{ generalData.radius };
		sf::CircleShape lowerRight{ generalData.radius };

		upperLeft.setOrigin(generalData.radius, generalData.radius);
		upperRight.setOrigin(generalData.radius, generalData.radius);
		lowerLeft.setOrigin(generalData.radius, generalData.radius);
		lowerRight.setOrigin(generalData.radius, generalData.radius);

		upperLeft.setPosition(specificData.origin.x - totalBoxLenght / 2.f + generalData.radius, specificData.origin.y - totalBoxHeight / 2.f + generalData.radius);
		upperRight.setPosition(specificData.origin.x + totalBoxLenght / 2.f - generalData.radius, specificData.origin.y - totalBoxHeight / 2.f + generalData.radius);
		lowerLeft.setPosition(specificData.origin.x - totalBoxLenght / 2.f + generalData.radius, specificData.origin.y + totalBoxHeight / 2.f - generalData.radius);
		lowerRight.setPosition(specificData.origin.x + totalBoxLenght / 2.f - generalData.radius, specificData.origin.y + totalBoxHeight / 2.f - generalData.radius);

		roundsForRoundedBox.push_back(upperLeft);
		roundsForRoundedBox.push_back(upperRight);
		roundsForRoundedBox.push_back(lowerLeft);
		roundsForRoundedBox.push_back(lowerRight);

		for (auto& shapeIt : roundsForRoundedBox)
		{
			shapeIt.setFillColor(sf::Color::Cyan);
		}
	}
}

void TextBox::draw(sf::RenderWindow& window)
{
	for (auto circles : roundsForRoundedBox)
	{
		window.draw(circles);
	}
	for (auto shapeIt : visibleShapesOfBox)
	{
		window.draw(shapeIt);
	}
	window.draw(visibleText);
	window.draw(textForTestIntelligentLine);
	textContainer.drawCursor(window);
}

sf::FloatRect TextBox::getFloatRect() const
{
	return textAndClickableArea;
}

void TextBox::addUniCodeCharacter(int newCharacter)
{
	textContainer.addChar(newCharacter);
	textContainer.updateVisibleText(visibleText);

	wordContainer.fillTextFormTextBox(textForTestIntelligentLine);
}

void TextBox::removeCharacter(bool direction)
{
	textContainer.removeChar();

	textContainer.updateVisibleText(visibleText);
}

void TextBox::newLine()
{
	textContainer.addNewLine();

	textContainer.updateVisibleText(visibleText);
}

Line* TextBox::getLine()
{
	return &wordContainer;
}