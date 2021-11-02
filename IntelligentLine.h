#pragma once
#include "Word.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Logging.h"

class IntelligentLine
{
public:
	IntelligentLine();
	std::pair<Word*, unsigned int> addChar(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	void fillTextFormTextBox(sf::Text& textFormBox);
	//std::pair<Word*, unsigned int> removeLeftChar(unsigned int posOfCursor, Word* currentWord);

private:

	std::pair<Word*, unsigned int> addCharFarLeftString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharFarLeftStringVeryFirstWord(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharFarLeftStringIsEnd(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharFarLeftStringInCenterOfLine(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	

	std::pair<Word*, unsigned int> addCharFarRightString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharFarRightStringIsEnd(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharFarRightStringInCenterOfLine(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);

	std::pair<Word*, unsigned int> addCharInCenterString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharInCenterStringSpace(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCharInCenterStringLetter(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord);
	std::pair<Word*, unsigned int> addCoupleCurrenWordWithNeighbors(Word* currentWord, std::shared_ptr<Word> leftWord, std::shared_ptr<Word> rightWord);


	//std::pair<Word*, unsigned int> checkLastCharOfLeftNeigbor(unsigned int posOfCursor, Word* currentWord);
	//std::pair<Word*, unsigned int> deleteLastCharOfLeftNeigbor(unsigned int posOfCursor, Word* currentWord);
	//std::pair<Word*, unsigned int> removeLeftWordBecauseItsEmpty(unsigned int posOfCursor, Word* currentWord);
	


	std::shared_ptr<Word> leftWord;

};

