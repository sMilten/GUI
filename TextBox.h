#pragma once
#include <SFML/Graphics.hpp>
#include "TextLiFoContainer.h"
#include "Line.h"

namespace TextboxData
{
	struct SpecificTextBoxData
	{
		SpecificTextBoxData(sf::Vector2f initOrigin, float initTextLenghtInPx, unsigned int initNumberOfVisibleLines);
		sf::Vector2f origin;
		float textLenghtInPx;
		unsigned int numberOfVisibleLines;
	};

	struct GeneralTextBoxData
	{
		GeneralTextBoxData(const sf::Text& initText, sf::Vector2f initDistanceTextToInnerFrame, sf::Vector2f initFrameThickness, float initCorrectionToBottom = 0, float initRadius = 0);
		sf::Text text;
		sf::Vector2f distanceTextToInnerFrame;
		sf::Vector2f frameThickness;
		float correctionToBottom;
		float radius;
	};
}

class TextBox
{
public:
	enum class boxForm
	{
		square,
		rounded
	};

	TextBox(sf::Vector2f setOrigin, float setTextLenght, int initNoOfVisibleLines, const sf::Text& initText, sf::Vector2f distanceTextToInnerFrame, sf::Vector2f frameThickness, float correctionToBottom = 0, float radius = -1);
	TextBox(TextboxData::GeneralTextBoxData generalData, TextboxData::SpecificTextBoxData specificData);

	
	void draw(sf::RenderWindow& window);
	sf::FloatRect getFloatRect() const;
	void addUniCodeCharacter(int newCharacter);
	void removeCharacter(bool direction = false); // true = right; left = false? What about enum class?
	void newLine();

	//void updateEndOfString(sf::String character, bool deleteLastChar = false);
	//void variableLenghtOfText();
	//void fixLengthOfText();
	//void setOneLined();
	//void setMultiLined(int numberOfLines = -1);

	/*  Test Line.h */
	Line* getLine();

private:
	std::vector<sf::RectangleShape> visibleShapesOfBox;
	std::vector<sf::CircleShape> roundsForRoundedBox;

	float textLengthInPx;
	TextLiFoContainer textContainer;
	sf::Text visibleText;
	std::wstring textContent;

	sf::Vector2f upperLeftCornerForText;
	sf::FloatRect textAndClickableArea;

	/*  Test Line.h */
	sf::RectangleShape testShape;
	Line wordContainer;
	sf::Text textForTestIntelligentLine;
};