#include "GameState.h"

GameState::GameState(CoreResourceHolder& coreResources) :
	coreResourceRef{ coreResources },
	inputHandler{ std::make_unique<InputHandler>(coreResources.getWindow()) }
{}

GameState::~GameState() {}

void GameState::bindEndFkr(const sf::String& nextState, ICommand& commandAsKey)
{
	endStateFtr = std::bind(&GameState::endThisState, this, nextState);
}

void GameState::addButton(std::unique_ptr<Button> button, std::unique_ptr<ICommand> ic, const sf::String& uiName) {
	interfaceModul.addButton(std::move(button), std::move(ic), uiName);
}

void GameState::addUI(const sf::String& initUIName, StateInterfaceHolder::uiState defaultUIState, const sf::FloatRect& uiRectForMouseclicks) {
	GameState::interfaceModul.addUI(initUIName, defaultUIState, uiRectForMouseclicks);
}

void GameState::addSprite(const sf::String& uiName, const sf::Texture& initTexture, sf::Vector2f initPosition) {
	interfaceModul.addSprite(uiName, initTexture, initPosition);
}

void GameState::addGUIInformation(const sf::String& nameOfUI, const sf::String& nameOfGUIObject, sf::Vector2f initPosition)
{
	interfaceModul.addGUIInformation(nameOfUI, nameOfGUIObject, initPosition);
}

void GameState::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode)
{
	interfaceModul.addTextToGUI(nameOfUI, nameofGUIObject, initAlignment, distanceToLastElement, initText, initRef, clockMode);
}

void GameState::updateSpecificUI(const sf::String& nameOfUIToUpdate, const sf::String& nameOfTextToUpdate)
{
	interfaceModul.updateSpecificUI(nameOfUIToUpdate, nameOfTextToUpdate);
}

void GameState::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText)
{
	interfaceModul.addTextToGUI(nameOfUI, nameofGUIObject, initAlignment, distanceToLastElement, initText);
}

void GameState::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite)
{
	interfaceModul.addTextToGUI(nameOfUI, nameofGUIObject, initAlignment, distanceToLastElement, initSprite);
}

StateInterfaceHolder& GameState::getInterfaceForToggleCommand() {
	return interfaceModul;
}

void GameState::interfaceBindKeyToCommand(StateInterfaceHolder::KeyBindType type, StateInterfaceHolder::LinkTag tag, sf::Keyboard::Key key, std::unique_ptr<ICommand> icPtr) {
	interfaceModul.bindKeyToCommand(type, tag, key, std::move(icPtr));
}

void GameState::addTextBox(const sf::String& textBoxName, bool visibiltyState, std::unique_ptr<TextBox> textBox)
{
	interfaceModul.addTextBox(textBoxName, visibiltyState, std::move(textBox));
}

void GameState::toggleTextBoxState(const sf::String& textBoxName)
{
	interfaceModul.toggleTextBoxState(textBoxName);
}

void GameState::initTextObject(sf::Text& textRef, const sf::String& buttonText, int charSize, const sf::Font& buttonFont)
{
	textRef.setString(buttonText);
	textRef.setCharacterSize(charSize);
	textRef.setFont(buttonFont);
	textRef.setFillColor(sf::Color::Black);
}

void GameState::endThisState(sf::String nextState)
{
	endStateFtr = nullptr;
	interfaceModul.resetUI();
	doActionsBeforeEnd(nextState);
}

void GameState::setInputHandlerMaps()
{
	inputHandler->setKeyEvent(interfaceModul.getKeyEventMap(), interfaceModul.getCommandEventMap());
	inputHandler->setKeyRealtime(interfaceModul.getKeyRealtimeMap(), interfaceModul.getCommandRealtimeMap());
	inputHandler->setUIMapForMouseClicks(interfaceModul.getActiveUIs());
	inputHandler->setTextBoxes(interfaceModul.getTextBoxes());
	inputHandler->setDefaultKeyboardHandling();
}

void GameState::update(sf::Time dt)
{
	if (endStateFtr != nullptr)
		endStateFtr();

	interfaceModul.update(dt);
}

void GameState::draw(sf::RenderWindow& window)
{
	window.setView(coreResourceRef.getUIView());
	interfaceModul.draw(window);
}

void GameState::handleInput()
{
	inputHandler->handleInput();
}