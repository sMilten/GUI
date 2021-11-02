#pragma once
#include "TextLiFoCell.h"
#include "TextCursor.h"

class TextLiFoContainer
{
public:
	TextLiFoContainer(const sf::Text& textRef, int numberOfLines, int initMaxLengthInPx);
	void addChar(wchar_t newChar);
	void removeChar();
	void addNewLine();
	void updateVisibleText(sf::Text& textToUpdate) const;
	std::vector<TextLiFoCell> getContent() const;	// ÄNDERN!!!!! Ich gebe ja was nach außen!!!

	void linkCursor(sf::Vector2f startPosition);
	void deLinkCursor();
	void drawCursor(sf::RenderWindow& window);

private:
	const sf::Font& font;
	unsigned int charSize;
	std::vector<unsigned char> wordBreakVector;

	std::vector<TextLiFoCell> textCells;
	int lengthOfALine;
	int maxNoLines;
	int currentLine;
	TextLiFoCell* currentTextCell;

	TextCursor textCursor;
};

