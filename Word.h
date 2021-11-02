#pragma once
#include <SFML/Graphics.hpp>

class Word
{
public:
	Word();
	Word(wchar_t initChar);
	void addChar(wchar_t charToAdd, unsigned int posOfCursor);
	void removeChar(unsigned int posOfCursor);

	Word* getLeftWord();
	Word* getRightWord();
	void setLeftWord(Word* leftWord);
	void setRightWord(Word* rightWord);
	unsigned int getSize();
	wchar_t getCharByPos(unsigned int posOfCursor);
	wchar_t getFirstChar();
	wchar_t getLastChar();
	void clear(wchar_t charToAdd);
	const std::wstring& getContent();

private:
	std::wstring content;
	Word* leftNeighbor;
	Word* rightNeigbor;

};

