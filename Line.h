#pragma once
#include <SFML/Graphics.hpp>

class Line
{
public:
	Line();
	std::wstring* getElement(unsigned int cursorPos);
	void insert(unsigned int cursorPos, const std::wstring& stringToAdd);
	void erase(unsigned int cursorPos);
	void fillTextFormTextBox(sf::Text& textToFill) const;
	unsigned int getSize() const;
	wchar_t getCharFromString(unsigned int cursorPos, unsigned int posInString);

private:
	std::vector<std::wstring> lineContent;

};