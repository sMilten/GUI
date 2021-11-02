#include "Line.h"

Line::Line() :
	lineContent{}
{}

std::wstring* Line::getElement(unsigned int cursorPos)
{
	return &lineContent.at(cursorPos - 1);
}

void Line::insert(unsigned int cursorPos, const std::wstring& stringToAdd)
{
	lineContent.insert(lineContent.begin() + cursorPos, std::wstring{ stringToAdd });
}

void Line::erase(unsigned int cursorPos)
{
	lineContent.erase(lineContent.begin() + cursorPos);
}

void Line::fillTextFormTextBox(sf::Text& textToFill) const
{
	std::wstring content;
	for (auto& str : lineContent)
	{
		content += str;
	}
	textToFill.setString(content);
}

unsigned int Line::getSize() const
{
	return lineContent.size();
}

wchar_t Line::getCharFromString(unsigned int cursorPos, unsigned int posInString)
{
	return lineContent.at(cursorPos).at(posInString);
}