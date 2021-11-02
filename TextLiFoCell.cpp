#include "TextLiFoCell.h"
#include <cassert>

TextLiFoCell::TextLiFoCell(const sf::Font& initFont, int initCharSize) :
	fontRef{initFont},
	lenghtOfLine{0},
	charSize{initCharSize}
{ }

void TextLiFoCell::addChar(wchar_t newChar)
{

	assert(newChar != L'\n');
	if (stringContainer.size() == 0)
	{
		stringContainer.push_back(std::wstring{ newChar });
	}
	else if (newChar == L' ' || newChar == L'\t')
	{
		stringContainer.push_back(std::wstring{ newChar });
	}
	else
	{
		if (stringContainer.back() == L" " || stringContainer.back() == L"\t")
		{
			stringContainer.push_back(std::wstring{ newChar });
		}
		else
		{
			stringContainer.back() += newChar;
		}
	}
	lenghtOfLine+= fontRef.getGlyph(newChar, charSize, false).advance;
}

float TextLiFoCell::removeChar()
{
	if (stringContainer.size() == 0)
	{
		return 0;
	}
	else if(stringContainer.back().size() == 1)
	{
		float lenghtToRemove = fontRef.getGlyph(stringContainer.back().back(), charSize, false).advance;
		lenghtOfLine -= lenghtToRemove;
		stringContainer.pop_back();
		return lenghtToRemove;
	}
	else
	{
		float lenghtToRemove = fontRef.getGlyph(stringContainer.back().back(), charSize, false).advance;
		lenghtOfLine -= lenghtToRemove;
		stringContainer.back().pop_back();
		return lenghtToRemove;
	}
}

float TextLiFoCell::getLengthInPx() const
{
	return lenghtOfLine;
}

float TextLiFoCell::getLenghtOfLastStringInPx() const
{
	if (stringContainer.size() == 0)
		return 0;

	float lenght = 0;
	for (auto& c : stringContainer.back())
	{
		lenght+= fontRef.getGlyph(c, charSize, false).advance;
	}
	return lenght;
}

unsigned int TextLiFoCell::getNumbersOfStrings() const
{
	return stringContainer.size();
}

void TextLiFoCell::removeLastString()
{
	for (auto& c : stringContainer.back())
	{
		lenghtOfLine -= fontRef.getGlyph(c, charSize, false).advance;
	}
	stringContainer.pop_back();
}

void TextLiFoCell::addStringToEnd(const std::wstring& newStr)
{
	stringContainer.push_back(newStr);
	for (auto& c : stringContainer.back())
	{
		lenghtOfLine += fontRef.getGlyph(c, charSize, false).advance;
	}
}

std::wstring TextLiFoCell::getLastString() const
{
	return stringContainer.back();
}

std::vector<std::wstring> TextLiFoCell::getContent() const
{
	return stringContainer;
}

void TextLiFoCell::fillsfString(sf::String& stringToFill) const
{
	for (auto c : stringContainer)
	{
		stringToFill += c;
	}
}