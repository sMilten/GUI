#pragma once
#include "Line.h"
#include "TextBox.h"

class CursorV2
{

public:
	CursorV2();
	void linkWordContainerViaTextBox(TextBox* boxWithTheContainer); // TODO: Relink
	void unlinkContainer();

	void addChar(wchar_t charToAdd);
	void removeChar();
	void moveCursorToTheLeft();
	void moveCursorToTheRight();

private:

	void insertFirstChar(wchar_t charToAdd);
	void cursorIsVeryLeft(wchar_t charToAdd);
	void cursorIsVeryRight(wchar_t charToAdd);
	void cursorIsInCenterOfLine(wchar_t charToAdd);
	void cursorIsInCenterOfLineCenterSpace(wchar_t charToAdd);
	void cursorIsInCenterOfLineCenterLetter(wchar_t charToAdd);
	void cursorIsInCenterOfLineEdgeSpace(wchar_t charToAdd);
	void cursorIsInCenterOfLineEdgeLetter(wchar_t charToAdd);

	std::wstring* stringPtr;
	unsigned int posInString;
	unsigned int currentStringNumber;
	Line* containerPtr;

};