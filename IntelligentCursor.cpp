#include "IntelligentCursor.h"
#include <iostream>

void IntelligentCursor::addChar(wchar_t charToAdd)
{
	if (currentWord != nullptr)
	{
		//std::cout << "Cursor Word Adress before: " << currentWord << " Size: " << currentWord->getSize() << std::endl;
	}
	
	std::pair<Word*, unsigned int> newPos = currentLine->addChar(charToAdd, cursorPosition, currentWord);

	currentWord = newPos.first;	// ------------------ GROßES PROBLEM: "Altes" Word wird überschrieben/freigegeben! -> Ptr muss seinen Inhalt "vergessen" (der alte bleibt bestehen!) und auf neuen Inhalt zeigen
	cursorPosition = newPos.second;
	if (currentWord != nullptr)
	{
		std::cout << currentWord->getLeftWord() << std::endl;
	}

	//std::cout << "CursorPosition_PAIR: " << newPos.second << "CursorPosition_MY: " << cursorPosition << std::endl;
	//std::cout << "Cursor Word Adress after: " << currentWord << " Size: " << currentWord->getSize() << std::endl;
}

void IntelligentCursor::linkTextBox(TextBox* boxToLink)
{
	selectedTextBox = boxToLink;
	currentLine = boxToLink->getIntelligentLine();
}