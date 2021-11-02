#include "IntelligentLine.h"
#include <cassert>

IntelligentLine::IntelligentLine() :
	leftWord{}
{
}

std::pair<Word*, unsigned int> IntelligentLine::addChar(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (currentWord != nullptr)
	{
		std::cout << currentWord << " Size: " << posOfCursor << ".getSize(): " << currentWord->getSize() << std::endl;
	}

	if (posOfCursor == 0)
	{
		ENTER("LEFT");
		return addCharFarLeftString(charToAdd, posOfCursor, currentWord);
	}
	else if (posOfCursor == currentWord->getSize())
	{
		ENTER("RIGHT");
		return addCharFarRightString(charToAdd, posOfCursor, currentWord);
	}
	else
	{
		ENTER("CENTER");
		return addCharInCenterString(charToAdd, posOfCursor, currentWord);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarLeftString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (currentWord == nullptr)
	{
		ENTER("LEFT FIRSTWORD");
		return addCharFarLeftStringVeryFirstWord(charToAdd, posOfCursor, currentWord);
	}
	else if (currentWord->getLeftWord() == nullptr)
	{
		ENTER("LEFT NEWWORD LEFT");
		return addCharFarLeftStringIsEnd(charToAdd, posOfCursor, currentWord);
	}
	else
	{
		ENTER("LEFT NEWORD CENTER");
		return addCharFarLeftStringInCenterOfLine(charToAdd, posOfCursor, currentWord);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarLeftStringVeryFirstWord(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	leftWord = std::make_shared<Word>(charToAdd);
	currentWord = leftWord.get();
	return std::pair<Word*, unsigned int>(currentWord, 1);
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarLeftStringIsEnd(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd == L' ')
	{
		if (currentWord->getFirstChar() == L' ')
		{
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			std::shared_ptr<Word> leftestWord = std::make_shared<Word>(charToAdd);
			leftWord = leftestWord;
			leftestWord->setRightWord(currentWord);
			currentWord->setLeftWord(leftestWord.get());
			return std::pair<Word*, unsigned int>(leftWord.get(), 1);
		}
	}
	else
	{
		if (currentWord->getFirstChar() != L' ')
		{
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			std::shared_ptr<Word> leftestWord = std::make_shared<Word>(charToAdd);
			leftWord = leftestWord;
			leftestWord->setRightWord(currentWord);
			currentWord->setLeftWord(leftWord.get());
			return std::pair<Word*, unsigned int>(leftWord.get(), 1);
		}
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarLeftStringInCenterOfLine(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd == L' ')
	{
		if (currentWord->getFirstChar() == L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{

			currentWord->getLeftWord()->addChar(charToAdd, currentWord->getLeftWord()->getSize());
			return std::pair<Word*, unsigned int>(currentWord->getLeftWord(), currentWord->getLeftWord()->getSize());
		}
	}
	else
	{
		if (currentWord->getFirstChar() != L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			currentWord->getLeftWord()->addChar(charToAdd, currentWord->getLeftWord()->getSize());
			return std::pair<Word*, unsigned int>(currentWord->getLeftWord(), currentWord->getLeftWord()->getSize());
		}
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarRightString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (currentWord->getRightWord() == nullptr)
	{
		ENTER("VERY RIGHT");
		return addCharFarRightStringIsEnd(charToAdd, posOfCursor, currentWord);
	}
	else
	{
		ENTER("RIGHT CENTER");
		return addCharFarRightStringInCenterOfLine(charToAdd, posOfCursor, currentWord);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarRightStringIsEnd(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd == L' ')
	{
		if (currentWord->getLastChar() == L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor+1);
		}
		else
		{
			ENTER("NEW SPACE");
			std::shared_ptr<Word> rightestWord = std::make_shared<Word>(charToAdd);
			rightestWord->setLeftWord(currentWord);
			currentWord->setRightWord(rightestWord.get());
			std::cout << "RIGHT ADRESS: " << rightestWord << " and SIZE: " << rightestWord->getSize() << std::endl;
			return std::pair<Word*, unsigned int>(rightestWord.get(), 1);
		}
	}
	else
	{
		if (currentWord->getLastChar() != L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			std::shared_ptr<Word> rightestWord = std::make_shared<Word>(charToAdd);
			rightestWord->setLeftWord(currentWord);
			currentWord->setRightWord(rightestWord.get());
			return std::pair<Word*, unsigned int>(rightestWord.get(), 1);
		}
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharFarRightStringInCenterOfLine(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd == L' ')
	{
		if (currentWord->getLastChar() == L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			currentWord->getRightWord()->addChar(charToAdd, 0);
			return std::pair<Word*, unsigned int>(currentWord->getRightWord(), 0);
		}
	}
	else
	{
		if (currentWord->getLastChar() != L' ')
		{
			currentWord->addChar(charToAdd, posOfCursor);
			return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
		}
		else
		{
			currentWord->getRightWord()->addChar(charToAdd, 0);
			return std::pair<Word*, unsigned int>(currentWord->getRightWord(), 0);
		}
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharInCenterString(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (currentWord->getCharByPos(posOfCursor) == L' ' && currentWord->getCharByPos(posOfCursor + 1) == L' ')
	{
		return addCharInCenterStringSpace(charToAdd, posOfCursor, currentWord);
	}
	else if(currentWord->getCharByPos(posOfCursor) != L' ' && currentWord->getCharByPos(posOfCursor + 1) != L' ')
	{
		return addCharInCenterStringLetter(charToAdd, posOfCursor, currentWord);
	}
	else
	{
		std::cout << "WHAT???? o.O -- das ist ein MEGA Fail... Sollte niemals eintreffen!" << std::endl;
		assert(1 == 0);
		return std::pair<Word*, unsigned int>(currentWord, 0);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharInCenterStringSpace(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd == L' ')
	{
		currentWord->addChar(charToAdd, posOfCursor);
		return std::pair<Word*, unsigned int>(currentWord, posOfCursor+1);
	}
	else
	{
		std::shared_ptr<Word> leftWord = std::make_shared<Word>();
		std::shared_ptr<Word> rightWord = std::make_shared<Word>();
		for (unsigned int i = 0; i < posOfCursor; i++)
		{
			leftWord->addChar(currentWord->getCharByPos(i), i);
		}
		for (unsigned int i = posOfCursor; i < currentWord->getSize()-1; i++)
		{
			rightWord->addChar(currentWord->getCharByPos(i), i);
		}
		currentWord->clear(charToAdd);
		return addCoupleCurrenWordWithNeighbors(currentWord, leftWord, rightWord);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCharInCenterStringLetter(wchar_t charToAdd, unsigned int posOfCursor, Word* currentWord)
{
	if (charToAdd != L' ')
	{
		currentWord->addChar(charToAdd, posOfCursor);
		return std::pair<Word*, unsigned int>(currentWord, posOfCursor + 1);
	}
	else
	{
		std::shared_ptr<Word> leftWord = std::make_shared<Word>();
		std::shared_ptr<Word> rightWord = std::make_shared<Word>();
		for (unsigned int i = 0; i < posOfCursor; i++)
		{
			leftWord->addChar(currentWord->getCharByPos(i), i);
		}
		for (unsigned int i = posOfCursor; i < currentWord->getSize() - 1; i++)
		{
			rightWord->addChar(currentWord->getCharByPos(i), i);
		}
		currentWord->clear(charToAdd);
		return addCoupleCurrenWordWithNeighbors(currentWord, leftWord, rightWord);
	}
}

std::pair<Word*, unsigned int> IntelligentLine::addCoupleCurrenWordWithNeighbors(Word* currentWord, std::shared_ptr<Word> leftWord, std::shared_ptr<Word> rightWord)
{
	if (currentWord->getLeftWord() != nullptr)
	{
		currentWord->getLeftWord()->setRightWord(leftWord.get());
		leftWord->setLeftWord(currentWord->getLeftWord());
	}
	else
	{
		this->leftWord = leftWord;
	}

	leftWord->setRightWord(currentWord);
	currentWord->setLeftWord(leftWord.get());

	if (currentWord->getRightWord() != nullptr)
	{
		currentWord->getRightWord()->setLeftWord(rightWord.get());
		rightWord->setRightWord(currentWord->getRightWord());
	}
	rightWord->setLeftWord(currentWord);
	currentWord->setRightWord(rightWord.get());

	return std::pair<Word*, unsigned int>(currentWord, 1);
}

void IntelligentLine::fillTextFormTextBox(sf::Text& textFormBox)
{
	std::wstring text;
	Word* currentWord = leftWord.get();
	while (currentWord != nullptr)
	{
		text += currentWord->getContent();
		currentWord = currentWord->getLeftWord();
	}
	textFormBox.setString(text);
}








/*
std::pair<std::shared_ptr<Word>, unsigned int> IntelligentLine::removeLeftChar(unsigned int posOfCursor, std::shared_ptr<Word> currentWord)
{
	if (posOfCursor == 0)
	{
		return checkLastCharOfLeftNeigbor(posOfCursor, currentWord);
	}
	else // Cursor befindet sich IN oder am Ende einem/eines Wort oder "zwischen" Zwei Wörtern
	{
		currentWord->removeChar(posOfCursor);
		// TODO
	}
}

std::pair<std::shared_ptr<Word>, unsigned int> IntelligentLine::checkLastCharOfLeftNeigbor(unsigned int posOfCursor, std::shared_ptr<Word> currentWord)
{

	if (currentWord->getLeftWord() != nullptr)
	{
		return deleteLastCharOfLeftNeigbor(posOfCursor, currentWord);
	}
	else
	{
		return std::pair<std::shared_ptr<Word>, unsigned int>(currentWord, posOfCursor);
	}
}

std::pair<std::shared_ptr<Word>, unsigned int> IntelligentLine::deleteLastCharOfLeftNeigbor(unsigned int posOfCursor, std::shared_ptr<Word> currentWord)
{
	currentWord->getLeftWord()->removeChar(currentWord->getLeftWord()->getSize() - 1);

	if (currentWord->getLeftWord()->getSize() == 0)
	{
		return removeLeftWordBecauseItsEmpty(posOfCursor, currentWord);
	}
	else
	{
		return std::pair<std::shared_ptr<Word>, unsigned int>(currentWord->getLeftWord(), currentWord->getLeftWord()->getSize());
	}
}

std::pair<std::shared_ptr<Word>, unsigned int> IntelligentLine::removeLeftWordBecauseItsEmpty(unsigned int posOfCursor, std::shared_ptr<Word> currentWord) // Remove all references to the empty Word!
{
	std::shared_ptr<Word> leftWordOfLeftWord = currentWord->getLeftWord()->getLeftWord();
	currentWord->setLeftWord(leftWordOfLeftWord);

	if (leftWordOfLeftWord == nullptr)
	{
		leftWord = currentWord;
		return std::pair<std::shared_ptr<Word>, unsigned int>(nullptr, 0);
	}
	else
	{
		leftWord = leftWordOfLeftWord;
		leftWordOfLeftWord->setRightWord(currentWord);
		return std::pair<std::shared_ptr<Word>, unsigned int>(leftWordOfLeftWord, currentWord->getLeftWord()->getSize());
	}
}*/