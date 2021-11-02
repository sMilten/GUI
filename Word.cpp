#include "Word.h"
#include <cassert>

Word::Word() :
	content{  },
	leftNeighbor{ nullptr },
	rightNeigbor{ nullptr }
{}

Word::Word(wchar_t initChar) :
	content{ initChar },
	leftNeighbor{ nullptr },
	rightNeigbor{ nullptr }
{}

void Word::addChar(wchar_t charToAdd, unsigned int posOfCursor)
{

	if (posOfCursor == content.size())
	{
		content.push_back(charToAdd);
	}
	else
	{
		content.insert(posOfCursor, std::wstring{ charToAdd });
	}
}

void Word::removeChar(unsigned int posOfCursor)
{
	assert(posOfCursor < content.size());
	content.erase(content.begin() + posOfCursor);
}

Word* Word::getLeftWord()
{
	return leftNeighbor;
}

Word* Word::getRightWord()
{
	return rightNeigbor;
}

void Word::setLeftWord(Word* leftWord)
{
	leftNeighbor = leftWord;
}

void Word::setRightWord(Word* rightWord)
{
	rightNeigbor = rightWord;
}

unsigned int Word::getSize()
{
	return content.size();
}

wchar_t Word::getCharByPos(unsigned int posOfCursor)
{
	return content.at(posOfCursor);
}

wchar_t Word::getFirstChar()
{
	return content.front();
}

wchar_t Word::getLastChar()
{
	return content.back();
}

void Word::clear(wchar_t charToAdd)
{
	content.clear();
	content.push_back(charToAdd);
}

const std::wstring& Word::getContent()
{
	return content;
}