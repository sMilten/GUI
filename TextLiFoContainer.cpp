#include "TextLiFoContainer.h"
#include <cassert>

TextLiFoContainer::TextLiFoContainer(const sf::Text& textRef, int numberOfLines, int initMaxLengthInPx) :
	lengthOfALine{ initMaxLengthInPx },
	maxNoLines{ numberOfLines - 1 },
	currentLine{ 0 },
	font{ *textRef.getFont() },
	charSize{ textRef.getCharacterSize() }
{
	for (int i = 0; i < numberOfLines-1; i++)
	{
		wordBreakVector.push_back(0);
	}

	for (int i = 0; i < numberOfLines; i++)
	{
		textCells.push_back(TextLiFoCell(*textRef.getFont(), textRef.getCharacterSize()));
	}
	currentTextCell = &*textCells.begin();
}

void TextLiFoContainer::addChar(wchar_t newChar)
{
	assert(newChar != L'\n');

	float newLineLenght = currentTextCell->getLengthInPx() + font.getGlyph(newChar, charSize, false).advance;

	if (currentLine == maxNoLines && newLineLenght >= lengthOfALine)
	{
		return;
	}
	else if (newLineLenght < lengthOfALine)
	{
		currentTextCell->addChar(newChar);
		textCursor.addVerticalSpace(font.getGlyph(newChar, charSize, false).advance);
	}
	else if (newLineLenght >= lengthOfALine)
	{
		currentLine++;
		currentTextCell = &textCells.at(currentLine);
		if (newChar != L' ' && newChar != L'\t')
		{
			wordBreakVector.at(currentLine-1) = true;
			if ((textCells.at(currentLine - 1).getLenghtOfLastStringInPx() + font.getGlyph(newChar, charSize, false).advance) < lengthOfALine)
			{
				if (textCells.at(currentLine - 1).getLastString() != L" " && textCells.at(currentLine - 1).getLastString() != L"\t")
				{
					textCells.at(currentLine).addStringToEnd(textCells.at(currentLine - 1).getLastString());
					textCells.at(currentLine - 1).removeLastString();
				}
			}
			currentTextCell->addChar(newChar);
		}
		textCursor.newLine(true, textCells.at(currentLine).getLengthInPx());
	}
	else
	{
		assert(1 == 0);
	}

}

void TextLiFoContainer::removeChar()
{
	if (currentTextCell->getLengthInPx() == 0)
	{
		if (currentLine == 0)
		{
			return;
		}
		else
		{
			currentLine--;
			currentTextCell = &textCells.at(currentLine);
			textCursor.newLine(false, textCells.at(currentLine).getLengthInPx());
		}
	}
	else
	{
		textCursor.removeVerticalSpace(currentTextCell->removeChar());
		if (currentLine >= 1 && wordBreakVector.at(currentLine - 1) == 1 && textCells.at(currentLine).getNumbersOfStrings() == 1)
		{
			if ((textCells.at(currentLine).getLenghtOfLastStringInPx() + textCells.at(currentLine-1).getLengthInPx()) < lengthOfALine)
			{
				currentLine--;
				currentTextCell = &textCells.at(currentLine);
				wordBreakVector.at(currentLine) = false;
				textCells.at(currentLine).addStringToEnd(textCells.at(currentLine + 1).getLastString());
				textCells.at(currentLine + 1).removeLastString();
				textCursor.newLine(false, textCells.at(currentLine).getLengthInPx());
			}
			
		}
	}
}

void TextLiFoContainer::addNewLine()
{
	if (currentLine == maxNoLines)
	{
		return;
	}
	else
	{
		currentLine++;
		currentTextCell = &textCells.at(currentLine);
		textCursor.newLine(true, 0);
	}
}

std::vector<TextLiFoCell> TextLiFoContainer::getContent() const
{
	return textCells;
}

void TextLiFoContainer::updateVisibleText(sf::Text& textToUpdate) const
{
	sf::String content;
	for (auto& cells : textCells)
	{
		cells.fillsfString(content);
		content += L'\n';
	}
	textToUpdate.setString(content);
}

void TextLiFoContainer::linkCursor(sf::Vector2f startPosition)
{
	textCursor.link(charSize, startPosition);
}

void TextLiFoContainer::deLinkCursor()
{
	textCursor.deLink();
}

void TextLiFoContainer::drawCursor(sf::RenderWindow& window)
{
	textCursor.draw(window);
}