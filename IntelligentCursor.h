#pragma once
#include "TextBox.h"
#include "Word.h"

class IntelligentCursor
{
public:

	void addChar(wchar_t charToAdd);
	void linkTextBox(TextBox* boxToLink);

private:

	TextBox* selectedTextBox;
	IntelligentLine* currentLine;
	Word* currentWord;
	unsigned int cursorPosition;

};

