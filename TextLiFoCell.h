#pragma once
#include <SFML/Graphics.hpp>

class TextLiFoCell
{

public:
	TextLiFoCell(const sf::Font& initFont, int initCharSize);
	void addChar(wchar_t newChar);
	float removeChar();
	float getLengthInPx() const;
	float getLenghtOfLastStringInPx() const;
	unsigned int getNumbersOfStrings() const;

	void removeLastString();
	void addStringToEnd(const std::wstring& newStr);
	std::wstring getLastString() const;
	std::vector<std::wstring> getContent() const;		/// ---------------------------------- BLÖD
	void fillsfString(sf::String& stringToFill) const;

private:
	std::vector<std::wstring> stringContainer;
	float lenghtOfLine;
	const sf::Font& fontRef;
	int charSize;

};

