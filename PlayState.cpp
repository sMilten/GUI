#include "PlayState.h"

#include "GoToScreenCommand.h"
#include "ToggleUIVisibilityCommand.h"
#include "CloseWindowCommand.h"
#include "DoNothingCommand.h"
#include "MoveViewCommand.h"

#include "SpriteButton.h"
#include "HoverButton.h"
#include <cassert>

PlayState::PlayState(StateHandler& initStateHandler,
	sf::FloatRect uiDistanceToView, CoreResourceHolder& coreResources) :
	GameState{ coreResources },
	stateHandler{ initStateHandler },
	world{ coreResources },
	scroller{ coreResources.getMapView() }
{
	inputHandler.reset(new InputHandlerPlayState(coreResourceRef.getWindow()));
	// UI
	setRealtimeMaps();
	setupUserInterfaceMaps();

	gameMouseViewCommand = std::make_shared<DoNothingCommand>();
	assert(activeGameViewArea.top >= 0 && activeGameViewArea.left >= 0);
	assert(activeGameViewArea.width >= 0 && activeGameViewArea.height >= 0);
	activeGameViewArea = uiDistanceToView;
	setInputHandlerMaps();

	// activeGameViewArea
	// |-------|
	// |   G   |
	// |-------|

}

void PlayState::initMap(sf::Vector2f initTileSize, sf::Vector2i initTileNumber)
{
	world.initWorld(initTileSize, initTileNumber, activeGameViewArea);
	scroller.initMapInPx(sf::Vector2f{ initTileSize.x * initTileNumber.x, initTileSize.y * initTileNumber.y });
}

void PlayState::setScrollSpeed(sf::Vector2f initSpeed)
{
	scroller.setScrollSpeed(initSpeed);
}

void PlayState::update(sf::Time dt)
{
	scroller.update(dt);
	world.update(dt);
	GameState::update(dt);
}

void PlayState::draw(sf::RenderWindow& window)
{
	window.setView(coreResourceRef.getMapView());
	world.draw(window);

	GameState::draw(window);
}

void PlayState::setInputHandlerMaps()
{
	GameState::setInputHandlerMaps();

	float right = coreResourceRef.getMapView().getSize().x - activeGameViewArea.left - activeGameViewArea.width;
	float bottom = coreResourceRef.getMapView().getSize().x - activeGameViewArea.left - activeGameViewArea.width;
	sf::FloatRect colliderForHandler{ activeGameViewArea.left, activeGameViewArea.top, right, bottom };
	static_cast<InputHandlerPlayState*>(inputHandler.get())->setActiveGameViewArea(colliderForHandler);
	static_cast<InputHandlerPlayState*>(inputHandler.get())->setGameMouseViewCommand(gameMouseViewCommand);
}

void PlayState::doActionsBeforeEnd(const sf::String& nextState)
{
	stateHandler.changeState(nextState);
}

void PlayState::setRealtimeMaps()
{
	std::unique_ptr<MoveViewCommand> moveUpCommand = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Up, scroller);
	std::unique_ptr<MoveViewCommand> moveDownCommand = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Down, scroller);
	std::unique_ptr<MoveViewCommand> moveLeftCommand = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Left, scroller);
	std::unique_ptr<MoveViewCommand> moveRightCommand = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Right, scroller);

	interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType::Realtime, StateInterfaceHolder::LinkTag::ScrollViewUp, sf::Keyboard::W, std::move(moveUpCommand));
	interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType::Realtime, StateInterfaceHolder::LinkTag::ScrollViewDown, sf::Keyboard::S, std::move(moveDownCommand));
	interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType::Realtime, StateInterfaceHolder::LinkTag::ScrollViewLeft, sf::Keyboard::A, std::move(moveLeftCommand));
	interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType::Realtime, StateInterfaceHolder::LinkTag::ScrollViewRight, sf::Keyboard::D, std::move(moveRightCommand));

}

void PlayState::setupUserInterfaceMaps()
{
	setStandardUI();
	setOptionUI();
}

void PlayState::setStandardUI()
{
	addUI("A_StandardUI", StateInterfaceHolder::uiState::show, sf::FloatRect{ 50,50,100,100 });
	setStandardNormalsButtons();
	setHoverAreaButtons();
	addSprite("A_StandardUI", coreResourceRef.getInterfaceTexture("1920_128"), sf::Vector2f{ 1920/2.f,64 });
	addSprite("A_StandardUI", coreResourceRef.getInterfaceTexture("128_1080"), sf::Vector2f{ 64,1080/2.f });
}

void PlayState::setStandardNormalsButtons()
{
	std::unique_ptr<ToggleUIVisibilityCommand> toggleOptionCommand = std::make_unique<ToggleUIVisibilityCommand>("B_RightOptionUI", getInterfaceForToggleCommand());
	std::unique_ptr<SpriteButton> toggleOptionButton = std::make_unique<SpriteButton>(sf::Vector2f(100, 100), coreResourceRef.getInterfaceTexture("GearNormal"));
	toggleOptionButton->setSelectedSprite(coreResourceRef.getInterfaceTexture("GearSelected"));
	addButton(std::move(toggleOptionButton), std::move(toggleOptionCommand), "A_StandardUI");
}

void PlayState::setHoverAreaButtons()
{

	std::unique_ptr<DoNothingCommand> dummyCommand0 = std::make_unique<DoNothingCommand>();
	std::unique_ptr<DoNothingCommand> dummyCommand1 = std::make_unique<DoNothingCommand>();
	std::unique_ptr<DoNothingCommand> dummyCommand2 = std::make_unique<DoNothingCommand>();
	std::unique_ptr<DoNothingCommand> dummyCommand3 = std::make_unique<DoNothingCommand>();
	
	std::unique_ptr<MoveViewCommand> hoveringUp = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Up, scroller);
	std::unique_ptr<HoverButton> hoverUpButton = std::make_unique<HoverButton>(sf::FloatRect(0, 0, coreResourceRef.getUIView().getSize().x, 2), std::move(hoveringUp));
	addButton(std::move(hoverUpButton), std::move(dummyCommand0), "A_StandardUI");

	std::unique_ptr<MoveViewCommand> hoveringDown = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Down, scroller);
	std::unique_ptr<HoverButton> hoverDownButton = std::make_unique<HoverButton>(sf::FloatRect(0, coreResourceRef.getUIView().getSize().y - 1, coreResourceRef.getUIView().getSize().x, 2), std::move(hoveringDown));
	addButton(std::move(hoverDownButton), std::move(dummyCommand1), "A_StandardUI");

	std::unique_ptr<MoveViewCommand> hoveringLeft = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Left, scroller);
	std::unique_ptr<HoverButton> hoverLeftButton = std::make_unique<HoverButton>(sf::FloatRect(0, 0, 2, coreResourceRef.getUIView().getSize().y), std::move(hoveringLeft));
	addButton(std::move(hoverLeftButton), std::move(dummyCommand2), "A_StandardUI");

	std::unique_ptr<MoveViewCommand> hoveringRight = std::make_unique<MoveViewCommand>(ScreenScroller::ViewMovmentDirection::Right, scroller);
	std::unique_ptr<HoverButton> hoverRightButton = std::make_unique<HoverButton>(sf::FloatRect(coreResourceRef.getUIView().getSize().x - 2, 0, 2, coreResourceRef.getUIView().getSize().y), std::move(hoveringRight));
	addButton(std::move(hoverRightButton), std::move(dummyCommand3), "A_StandardUI");
}

void PlayState::setOptionUI()
{
	addUI("B_RightOptionUI", StateInterfaceHolder::uiState::hide, sf::FloatRect{ 660, 330, 600, 420 });
	setOptionButtons();
	addSprite("B_RightOptionUI", coreResourceRef.getInterfaceTexture("GreenBackground"), sf::Vector2f(1920 / 2.f, 1080 / 2.f));
}

void PlayState::setOptionButtons()
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

	std::unique_ptr<GoToScreenCommand> optionCommand1 = std::make_unique<GoToScreenCommand>("MainMenu_State", *this);
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