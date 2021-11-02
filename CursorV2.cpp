#include "CursorV2.h"
#include <iostream>

CursorV2::CursorV2() :
	stringPtr{ nullptr },
	posInString{ 0 },
	currentStringNumber{ 0 },
	containerPtr{ nullptr }
{ }

void CursorV2::linkWordContainerViaTextBox(TextBox* boxWithTheContainer)
{
	containerPtr = boxWithTheContainer->getLine();
}

void CursorV2::unlinkContainer()
{
	stringPtr = nullptr;
	containerPtr = nullptr;
	posInString = 0;		// orientated towards string.size() (0 is the first Char!)
	currentStringNumber = 0;		// orientated towards vector.size() (0 means no Strings!)
}

void CursorV2::addChar(wchar_t charToAdd)
{

	if (containerPtr->getSize() == 0)
	{
		insertFirstChar(charToAdd);
	}
	else if (currentStringNumber == 1 && posInString == 0)
	{
		cursorIsVeryLeft(charToAdd);
	}
	else if (currentStringNumber == containerPtr->getSize() && posInString == stringPtr->size())
	{
		cursorIsVeryRight(charToAdd);
	}
	else
	{
		cursorIsInCenterOfLine(charToAdd);
	}
}

void CursorV2::removeChar()
{
	// TODO!!! - First check void CursorV2::addChar(wchar_t charToAdd) !!!
}

void CursorV2::moveCursorToTheLeft()
{
	if (containerPtr->getSize() != 0)
	{
		if (posInString == 0)
		{
			if (currentStringNumber == 1)
			{
				return;
			}
			currentStringNumber--;
			stringPtr = containerPtr->getElement(currentStringNumber);
			posInString = stringPtr->size() - 1;
		}
		else
		{
			posInString--;
		}
	}
}

void CursorV2::moveCursorToTheRight()
{
	if (containerPtr->getSize() != 0)
	{
		if (posInString == stringPtr->size())
		{
			if (currentStringNumber == containerPtr->getSize())
			{
				return;
			}
			currentStringNumber++;
			stringPtr = containerPtr->getElement(currentStringNumber);
			posInString = 1; // wenn 0, dann wechselt der einfach nur den String, ohne wirklich nach vorne zu gehen
		}
		else
		{
			posInString++;
		}
	}
}

void CursorV2::insertFirstChar(wchar_t charToAdd)
{
	containerPtr->insert(0, std::wstring{ charToAdd });
	currentStringNumber++;
	posInString++;
	stringPtr = containerPtr->getElement(currentStringNumber);
}

void CursorV2::cursorIsVeryRight(wchar_t charToAdd)
{
	if (charToAdd == L' ')
	{
		if(stringPtr->back() == L' ')
		{
			stringPtr->push_back(charToAdd);
			posInString++;
		}
		else
		{
			containerPtr->insert(currentStringNumber, std::wstring{ charToAdd });
			currentStringNumber++;
			posInString = 1;
			stringPtr = containerPtr->getElement(currentStringNumber);
		}
	}
	else
	{
		if (stringPtr->back() != L' ')
		{
			stringPtr->push_back(charToAdd);
			//stringPtr->insert(stringPtr->begin() + posInString, charToAdd);
			posInString++;
		}
		else
		{
			containerPtr->insert(currentStringNumber, std::wstring{ charToAdd });
			currentStringNumber++;
			posInString = 1;
			stringPtr = containerPtr->getElement(currentStringNumber);
		}
	}
}

void CursorV2::cursorIsVeryLeft(wchar_t charToAdd)
{
	if (charToAdd == L' ')
	{
		if (stringPtr->front() == L' ')
		{
			stringPtr->insert(stringPtr->begin(), charToAdd);
			posInString++;
		}
		else
		{
			containerPtr->insert(0, std::wstring{ charToAdd });
			currentStringNumber = 1;
			posInString = 1;
			stringPtr = containerPtr->getElement(currentStringNumber);
		}
	}
	else
	{
		if (stringPtr->front() != L' ')
		{
			stringPtr->insert(stringPtr->begin(), charToAdd);
			posInString++;
		}
		else
		{
			containerPtr->insert(0, std::wstring{ charToAdd });
			currentStringNumber = 1;
			posInString = 1;
			stringPtr = containerPtr->getElement(currentStringNumber);
		}
	}
}

void CursorV2::cursorIsInCenterOfLine(wchar_t charToAdd)
{
	if (posInString > 0 && posInString < stringPtr->size())	// Strings with size = 1 are excluded from this (they go to else)
	{
		if (charToAdd == L' ')
		{
			cursorIsInCenterOfLineCenterSpace(charToAdd);
		}
		else
		{
			cursorIsInCenterOfLineCenterLetter(charToAdd);
		}
	}
	else
	{
		// an den Rändern von Wörtern (links oder rechts) ABER: mitten in der Zeil!
		if (charToAdd == L' ')
		{
			cursorIsInCenterOfLineEdgeSpace(charToAdd);
		}
		else
		{
			cursorIsInCenterOfLineEdgeLetter(charToAdd);
		}
	}
}

void CursorV2::cursorIsInCenterOfLineCenterSpace(wchar_t charToAdd)
{
	if (containerPtr->getElement(currentStringNumber)->at(posInString) == L' ') // at(posInString+1) MUSS ja auch == L' ' sein!
	{
		containerPtr->getElement(currentStringNumber)->insert(containerPtr->getElement(currentStringNumber)->begin() + posInString, charToAdd);
		posInString++;
	}
	else // insert L' ' in a Word -> seperate them at <posInString> insert a new Word between the seperated Words
	{
		std::wstring newLeftWord;
		std::wstring newRightWord;
		for (unsigned int i = 0; i < posInString; i++)
		{
			newLeftWord += containerPtr->getElement(currentStringNumber)->at(i);
		}
		for (unsigned int i = posInString; i < containerPtr->getElement(currentStringNumber)->size(); i++)
		{
			newRightWord += containerPtr->getElement(currentStringNumber)->at(i);
		}
		*(containerPtr->getElement(currentStringNumber)) = std::wstring{ charToAdd };
		containerPtr->insert(currentStringNumber-1, newLeftWord);
		containerPtr->insert(currentStringNumber + 1, newRightWord);
		currentStringNumber++; // postion of the new inserted Word with charToAdd
		posInString = 1;
		stringPtr = containerPtr->getElement(currentStringNumber);
	}
}

void CursorV2::cursorIsInCenterOfLineCenterLetter(wchar_t charToAdd)
{
	if (containerPtr->getElement(currentStringNumber)->at(posInString) != L' ') // at(posInString+1) MUSS ja auch == L' ' sein!
	{
		containerPtr->getElement(currentStringNumber)->insert(containerPtr->getElement(currentStringNumber)->begin() + posInString, charToAdd);
		posInString++;
	}
	else // insert L' ' in a Word -> seperate them at <posInString> insert a new Word between the seperated Words
	{
		std::wstring newLeftWord;
		std::wstring newRightWord;
		for (unsigned int i = 0; i < posInString; i++)
		{
			newLeftWord += containerPtr->getElement(currentStringNumber)->at(i);
		}
		for (unsigned int i = posInString; i < containerPtr->getElement(currentStringNumber)->size(); i++)
		{
			newRightWord += containerPtr->getElement(currentStringNumber)->at(i);
		}
		*(containerPtr->getElement(currentStringNumber)) = std::wstring{ charToAdd };
		containerPtr->insert(currentStringNumber - 1, newLeftWord);
		containerPtr->insert(currentStringNumber + 1, newRightWord);
		currentStringNumber++; // postion of the new inserted Word with charToAdd
		posInString = 1;
		stringPtr = containerPtr->getElement(currentStringNumber);
	}
}

void CursorV2::cursorIsInCenterOfLineEdgeSpace(wchar_t charToAdd)
{
	if (posInString == 0)
	{
		if (containerPtr->getCharFromString(currentStringNumber - 1, posInString) == L' ')
		{
			containerPtr->getElement(currentStringNumber)->insert(containerPtr->getElement(currentStringNumber)->begin(), charToAdd);
			posInString++;
		}
		else
		{
			currentStringNumber--;
			stringPtr = containerPtr->getElement(currentStringNumber);
			stringPtr->push_back(charToAdd);
			posInString = stringPtr->size();
		}
	}
	else // posInString == stringPtr->size()
	{
		if (stringPtr->back() == L' ')
		{
			stringPtr->push_back(charToAdd);
			posInString++;
		}
		else
		{
			currentStringNumber++;
			stringPtr = containerPtr->getElement(currentStringNumber);
			stringPtr->insert(stringPtr->begin(), charToAdd);
			posInString = 1;
		}
	}
}

void CursorV2::cursorIsInCenterOfLineEdgeLetter(wchar_t charToAdd)
{
	if (posInString == 0)
	{
		if (containerPtr->getCharFromString(currentStringNumber - 1, posInString) != L' ')
		{
			containerPtr->getElement(currentStringNumber)->insert(containerPtr->getElement(currentStringNumber)->begin(), charToAdd);
			posInString++;
		}
		else
		{
			currentStringNumber--;
			stringPtr = containerPtr->getElement(currentStringNumber);
			stringPtr->push_back(charToAdd);
			posInString = stringPtr->size();
		}
	}
	else // posInString == stringPtr->size()
	{
		if (stringPtr->back() != L' ')
		{
			stringPtr->push_back(charToAdd);
			posInString++;
		}
		else
		{
			currentStringNumber++;
			stringPtr = containerPtr->getElement(currentStringNumber);
			stringPtr->insert(stringPtr->begin(), charToAdd);
			posInString = 1;
		}
	}
}