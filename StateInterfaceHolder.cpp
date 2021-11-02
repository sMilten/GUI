#include "StateInterfaceHolder.h"

#include <iostream>

StateInterfaceHolder::StateInterfaceHolder() :
	enumKeyBindingEvent{},
	enumCommandBindingEvent{},
	enumKeyBindingRealtime{},
	enumCommandBindingRealime{},
	activeUIs{},
	deactiveUIs{},
	defaultUIOrder{},
	activeTextBoxes{},
	deactiveTextBoxes{}
{}

StateInterfaceHolder::uiState StateInterfaceHolder::getUIVisibility(const sf::String& uiName)
{
	auto activeFound = activeUIs.find(uiName);
	auto deactiveFound = deactiveUIs.find(uiName);
	assert(activeFound != activeUIs.end() || deactiveFound != deactiveUIs.end());
	if (activeFound != activeUIs.end())
		return StateInterfaceHolder::uiState::show;
	else
		return StateInterfaceHolder::uiState::hide;
}

void StateInterfaceHolder::changeUIState(const sf::String& uiName, StateInterfaceHolder::uiState moveToState)
{
	auto itFoundActive = activeUIs.find(uiName);
	auto itFoundDeactive = deactiveUIs.find(uiName);
	assert((itFoundActive != activeUIs.end() || itFoundDeactive != deactiveUIs.end()) && getUIVisibility(uiName) != moveToState);

	if (moveToState == StateInterfaceHolder::uiState::hide)
	{
		assert(itFoundActive != activeUIs.end());
		deactiveUIs.insert(std::make_pair(itFoundActive->first, std::move(itFoundActive->second)));
		activeUIs.erase(itFoundActive);
	}
	else // moveToState == uiState::show
	{
		assert(itFoundDeactive != deactiveUIs.end());
		activeUIs.insert(std::make_pair(itFoundDeactive->first, std::move(itFoundDeactive->second)));
		deactiveUIs.erase(itFoundDeactive);
	}
}

void StateInterfaceHolder::draw(sf::RenderWindow& windowRef) const
{
	for (auto& it : activeUIs)
	{
		it.second->getBackground().draw(windowRef);
	}
	for (auto& itUI : activeUIs)
	{
		for (auto& itButtons : itUI.second->getButtons())
		{
			itButtons.first->draw(windowRef);
		}
	}
	for (auto& itUI : activeUIs)
	{
		for (auto& itInformation : itUI.second->getText())
		{
			itInformation.second.draw(windowRef);
		}
	}
	for (auto& itActiveBoxes : activeTextBoxes)
	{
		itActiveBoxes.second->draw(windowRef);
	}
}

void StateInterfaceHolder::update(sf::Time dt)
{
	for (auto& it : activeUIs)
	{
		it.second->update(dt);
	}
}

void StateInterfaceHolder::updateSpecificUI(const sf::String& nameOfUIToUpdate, const sf::String& nameOfTextToUpdate)
{
	auto foundUI = activeUIs.find(nameOfUIToUpdate);
	if (foundUI == activeUIs.end())
	{
		foundUI = deactiveUIs.find(nameOfUIToUpdate);
		foundUI = deactiveUIs.find(nameOfUIToUpdate);
		assert(foundUI != deactiveUIs.end());
	}
	foundUI->second->updateVaribleText(nameOfTextToUpdate);
}

void StateInterfaceHolder::resetUI()
{
	for (auto itMap : defaultUIOrder)
	{
		if (getUIVisibility(itMap.first) != itMap.second)
			changeUIState(itMap.first, itMap.second);
	}
}

void StateInterfaceHolder::addButton(std::unique_ptr<Button> button, std::unique_ptr<ICommand> ic, const sf::String& uiName)
{
	if (getUIVisibility(uiName) == StateInterfaceHolder::uiState::show)
	{
		activeUIs.find(uiName)->second->addButton(std::move(button), std::move(ic));
	}
	else
	{
		deactiveUIs.find(uiName)->second->addButton(std::move(button), std::move(ic));
	}
}

void StateInterfaceHolder::addSprite(const sf::String& uiName, const sf::Texture& initTexture, sf::Vector2f initPosition)
{
	auto itFound = activeUIs.find(uiName);
	if (itFound == activeUIs.end())
	{
		itFound = deactiveUIs.find(uiName);
		assert(itFound != deactiveUIs.end());
	}
	itFound->second->addSprite(initTexture, initPosition);
}

void StateInterfaceHolder::addUI(const sf::String& initUIName, StateInterfaceHolder::uiState defaultUIState, sf::FloatRect uiRectForMouseclicks)
{
	std::map<sf::String, std::unique_ptr<UserInterface>>::iterator itFound = activeUIs.find(initUIName);
	assert(itFound == activeUIs.end());
	itFound = deactiveUIs.find(initUIName);
	assert(itFound == deactiveUIs.end());

	if (defaultUIState == StateInterfaceHolder::uiState::show)
	{
		activeUIs.insert(std::make_pair(initUIName, std::make_unique<UserInterface>(uiRectForMouseclicks)));
	}
	else
	{
		deactiveUIs.insert(std::make_pair(initUIName, std::make_unique<UserInterface>(uiRectForMouseclicks)));
	}
	defaultUIOrder.insert(std::make_pair(initUIName, defaultUIState));
}

void StateInterfaceHolder::addGUIInformation(const sf::String& nameOfUI, const sf::String& nameOfGUIObject, sf::Vector2f initPosition)
{
	auto stateOfUI = defaultUIOrder.find(nameOfUI);
	assert(stateOfUI != defaultUIOrder.end());
	if (stateOfUI->second == uiState::show)
	{
		activeUIs.at(nameOfUI)->addGUIInformation(nameOfGUIObject, initPosition);
	}
	else
	{
		deactiveUIs.at(nameOfUI)->addGUIInformation(nameOfGUIObject, initPosition);
	}
}

void StateInterfaceHolder::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText, int& initRef, bool clockMode)
{
	auto stateOfUI = defaultUIOrder.find(nameOfUI);
	assert(stateOfUI != defaultUIOrder.end());
	if (stateOfUI->second == uiState::show)
	{
		activeUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initText, initRef, clockMode);
	}
	else
	{
		deactiveUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initText, initRef, clockMode);
	}
}

void StateInterfaceHolder::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Text initText)
{
	auto stateOfUI = defaultUIOrder.find(nameOfUI);
	assert(stateOfUI != defaultUIOrder.end());
	if (stateOfUI->second == uiState::show)
	{
		activeUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initText);
	}
	else
	{
		deactiveUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initText);
	}
}

void StateInterfaceHolder::addTextToGUI(const sf::String& nameOfUI, const sf::String& nameofGUIObject, GraphicalDisplayObject::formatting initAlignment, float distanceToLastElement, sf::Sprite initSprite)
{
	auto stateOfUI = defaultUIOrder.find(nameOfUI);
	assert(stateOfUI != defaultUIOrder.end());
	if (stateOfUI->second == uiState::show)
	{
		activeUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initSprite);
	}
	else
	{
		deactiveUIs.at(nameOfUI)->addTextToGUI(nameofGUIObject, initAlignment, distanceToLastElement, initSprite);
	}
}

void StateInterfaceHolder::addTextBox(const sf::String& textBoxName, bool visibiltyState, std::unique_ptr<TextBox> textBox)
{
	auto foundActive = activeTextBoxes.find(textBoxName);
	auto foundDeactive = deactiveTextBoxes.find(textBoxName);
	assert(foundActive == activeTextBoxes.end() && foundDeactive == deactiveTextBoxes.end());

	if (visibiltyState == true)
	{
		activeTextBoxes.insert(std::make_pair(textBoxName, std::move(textBox)));
	}
	else
	{
		deactiveTextBoxes.insert(std::make_pair(textBoxName, std::move(textBox)));
	}
}

void StateInterfaceHolder::toggleTextBoxState(const sf::String& textBoxName)
{
	auto foundAct = activeTextBoxes.find(textBoxName);
	auto foundDeact = deactiveTextBoxes.find(textBoxName);
	assert(foundAct != activeTextBoxes.end() || foundDeact != deactiveTextBoxes.end());

	if (foundAct != activeTextBoxes.end())
	{	
		activeTextBoxes.insert(std::make_pair(textBoxName, std::move(deactiveTextBoxes.at(textBoxName))));
		deactiveTextBoxes.erase(textBoxName);
	}
	else if(foundDeact != activeTextBoxes.end())
	{
		deactiveTextBoxes.insert(std::make_pair(textBoxName, std::move(deactiveTextBoxes.at(textBoxName))));
		activeTextBoxes.erase(textBoxName);
	}
}

void StateInterfaceHolder::bindKeyToCommand(KeyBindType type, LinkTag tag, sf::Keyboard::Key key, std::unique_ptr<ICommand> icPtr)
{
	if (type == KeyBindType::Event)
	{
		auto found = enumKeyBindingEvent.find(tag);
		if (found != enumKeyBindingEvent.end())
		{
			enumKeyBindingEvent.erase(tag);
			enumCommandBindingEvent.erase(tag);
		}
		enumKeyBindingEvent.insert(std::make_pair(tag, key));
		enumCommandBindingEvent.insert(std::make_pair(tag, std::move(icPtr)));
	}
	else   // type == KeyBindType::RealTime
	{
		auto found = enumKeyBindingRealtime.find(tag);
		if (found != enumKeyBindingRealtime.end())
		{
			enumKeyBindingRealtime.erase(tag);
			enumCommandBindingRealime.erase(tag);
		}
		enumKeyBindingRealtime.insert(std::make_pair(tag, key));
		enumCommandBindingRealime.insert(std::make_pair(tag, std::move(icPtr)));
	}
}