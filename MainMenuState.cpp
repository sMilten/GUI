#include "MainMenuState.h"

#include "GoToScreenCommand.h"
#include "DoNothingCommand.h"
#include "CloseWindowCommand.h"
#include "ToggleUIVisibilityCommand.h"
#include "SpriteButton.h"

#include <cassert>
#include <iostream>


MainMenuState::MainMenuState(StateHandler& initStateHandler, CoreResourceHolder& coreResources) :
	GameState{ coreResources },
	stateHandler{ initStateHandler },
	sec{ 0 },
	min{ 0 },
	hour{ 0 },
	elapsedTimeForClock{sf::Time::Zero}
{
	setupUserInterfaceMaps();
	setInputHandlerMaps();
}

void MainMenuState::update(sf::Time dt)
{
	GameState::update(dt);
	elapsedTimeForClock += dt;

	if (elapsedTimeForClock.asSeconds() >= 1)
	{
		elapsedTimeForClock -= sf::seconds(1);
		sec++;
		if (sec == 60)
		{
			sec = 0;
			min ++;
			if (min == 60)
			{
				hour++;
			}
		}
		updateSpecificUI("A_StandardUI", "TestClock");
	}

}

void MainMenuState::draw(sf::RenderWindow& window)
{
	GameState::draw(window);
}

void MainMenuState::doActionsBeforeEnd(const sf::String& nextState)
{
	stateHandler.changeState(nextState);
}

void MainMenuState::setupUserInterfaceMaps()
{
	setStandardUI();
	setOptionUI();
}

void MainMenuState::setStandardUI()
{
	addUI("A_StandardUI", StateInterfaceHolder::uiState::show, sf::FloatRect{ 50,50,100,100 });
	setStandardNormalsButtons();
	setStandardText();
	addSprite("A_StandardUI", coreResourceRef.getInterfaceTexture("MainMenuStateBackground"), sf::Vector2f(1920 / 2.f, 1080 / 2.f));
	setStandardTextBox();
}

void MainMenuState::setStandardNormalsButtons()
{
	std::unique_ptr<ToggleUIVisibilityCommand> toggleOptionCommand = std::make_unique<ToggleUIVisibilityCommand>("B_RightOptionUI", getInterfaceForToggleCommand());
	std::unique_ptr<SpriteButton> toggleOptionButton = std::make_unique<SpriteButton>(sf::Vector2f(100, 100), coreResourceRef.getInterfaceTexture("GearNormal"));
	toggleOptionButton->setSelectedSprite(coreResourceRef.getInterfaceTexture("GearSelected"));
	addButton(std::move(toggleOptionButton), std::move(toggleOptionCommand), "A_StandardUI");
}

void MainMenuState::setStandardTextBox() // WIP!
{
	sf::Text dummyText{};
	dummyText.setCharacterSize(20);
	dummyText.setFillColor(sf::Color::Black);
	dummyText.setString(":");
	dummyText.setFont(coreResourceRef.getFont("DieterSteffmann_MedivelFont"));
	TextboxData::GeneralTextBoxData generalData { dummyText, sf::Vector2f{ 3,3 }, sf::Vector2f{ 3,3 }, 0.f, 5.f };
	TextboxData::SpecificTextBoxData specificData { sf::Vector2f{ 300,300 }, 150.f, 4 };
	std::unique_ptr<TextBox> testBox = std::make_unique<TextBox>(generalData, specificData);
	//std::unique_ptr<TextBox> testBox = std::make_unique<TextBox>(sf::Vector2f{ 300,300 }, 150.f, 4, dummyText, sf::Vector2f{ 3,3 }, sf::Vector2f{ 3,3 }, 0.f, 5.f);
	addTextBox("TestTextBox", true, std::move(testBox));
}

void MainMenuState::setOptionUI()
{
	addUI("B_RightOptionUI", StateInterfaceHolder::uiState::hide, sf::FloatRect{ 660, 330, 600, 420 });
	setOptionButtons();
	addSprite("B_RightOptionUI", coreResourceRef.getInterfaceTexture("GreenBackground"), sf::Vector2f(1920 / 2.f, 1080 / 2.f));
}

void MainMenuState::setOptionButtons()
{
	sf::Text optionText0;
	sf::Text optionText1;
	sf::Text optionText2;
	initTextObject(optionText0, "NOT DEFINED", 20, coreResourceRef.getFont("DieterSteffmann_MedivelFont"));
	initTextObject(optionText1, "Go To Play_Screen", 20, coreResourceRef.getFont("DieterSteffmann_MedivelFont"));
	initTextObject(optionText2, "Quit", 20, coreResourceRef.getFont("DieterSteffmann_MedivelFont"));

	std::unique_ptr<DoNothingCommand> optionCommand0 = std::make_unique<DoNothingCommand>();
	std::unique_ptr<SpriteButton> optionButton0 = std::make_unique<SpriteButton>(sf::Vector2f(1920 / 2.f, 1080 / 2.f - 120), coreResourceRef.getInterfaceTexture("GreenButton"));
	optionButton0->setText(optionText0);
	optionButton0->setSelectedSprite(coreResourceRef.getInterfaceTexture("GreenButtonSelected"));
	optionButton0->setMainTextColor(sf::Color::Black);
	optionButton0->setSelectedTextColor(sf::Color::Black);
	addButton(std::move(optionButton0), std::move(optionCommand0), "B_RightOptionUI");

	std::unique_ptr<GoToScreenCommand> optionCommand1 = std::make_unique<GoToScreenCommand>("Play_State", *this);
	std::unique_ptr<SpriteButton> optionButton1 = std::make_unique<SpriteButton>(sf::Vector2f(1920 / 2.f, 1080 / 2.f), coreResourceRef.getInterfaceTexture("GreenButton"));
	optionButton1->setText(optionText1);
	optionButton1->setSelectedSprite(coreResourceRef.getInterfaceTexture("GreenButtonSelected"));
	optionButton1->setMainTextColor(sf::Color::Black);
	optionButton1->setSelectedTextColor(sf::Color::Black);
	addButton(std::move(optionButton1), std::move(optionCommand1), "B_RightOptionUI");

	std::unique_ptr<CloseWindowCommand> optionCommand2 = std::make_unique<CloseWindowCommand>(coreResourceRef.getWindow());
	std::unique_ptr<SpriteButton> optionButton2 = std::make_unique<SpriteButton>(sf::Vector2f(1920 / 2.f, 1080 / 2.f + 120), coreResourceRef.getInterfaceTexture("GreenButton"));
	optionButton2->setText(optionText2);
	optionButton2->setSelectedSprite(coreResourceRef.getInterfaceTexture("GreenButtonSelected"));
	optionButton2->setMainTextColor(sf::Color::Black);
	optionButton2->setSelectedTextColor(sf::Color::Black);
	addButton(std::move(optionButton2), std::move(optionCommand2), "B_RightOptionUI");
}

void MainMenuState::setStandardText()
{
	addGUIInformation("A_StandardUI", "TestClock", sf::Vector2f{100, 900});
	sf::Text dummyText{};
	dummyText.setCharacterSize(20);
	dummyText.setFillColor(sf::Color::Black);
	dummyText.setString(":");
	dummyText.setFont(coreResourceRef.getFont("DieterSteffmann_MedivelFont"));
	addTextToGUI("A_StandardUI", "TestClock", GraphicalDisplayObject::formatting::TopLeft, 0, dummyText, hour, true);
	addTextToGUI("A_StandardUI", "TestClock", GraphicalDisplayObject::formatting::TopLeft, 10, dummyText);
	addTextToGUI("A_StandardUI", "TestClock", GraphicalDisplayObject::formatting::TopLeft, 10, dummyText, min, true);
	addTextToGUI("A_StandardUI", "TestClock", GraphicalDisplayObject::formatting::TopLeft, 10, dummyText);
	addTextToGUI("A_StandardUI", "TestClock", GraphicalDisplayObject::formatting::TopLeft, 10, dummyText, sec, true);

}