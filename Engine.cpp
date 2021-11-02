#include "Engine.h"

#include "PlayState.h"
#include "MainMenuState.h"

int Engine::objectCounter = 0;
float Engine::screenWidth = 1920.f;
float Engine::screenHeight = 1080.f;
float Engine::ticksPerSecond = 60.f;

Engine::Engine() :
	dt{ sf::Time::Zero },
	tickLenght{ sf::seconds(1.f / Engine::ticksPerSecond) },
	window{ sf::VideoMode(1920,1080), "StateMachine", sf::Style::Close },
	coreResources{ window },
	stateHandler{ coreResources }
{
	objectCounter++;
	assert(objectCounter == 1);

	window.setVerticalSyncEnabled(true);

	stateHandler.initStates();
}

Engine::~Engine()
{
	objectCounter--;
}

void Engine::run()
{
	clk.restart();
	while (window.isOpen())
	{
		handleInput();
		dt += clk.restart();
		while (dt >= tickLenght)
		{
			update(tickLenght);
			dt -= tickLenght;
		}
		draw();
	}
}

void Engine::handleInput()
{
	stateHandler.handleInput();
}

void Engine::update(sf::Time dt)
{
	coreResources.getMouseSprite().updatePosition(dt);
	stateHandler.update(dt);
}

void Engine::draw()
{
	window.clear(sf::Color::White);

	stateHandler.draw();
	coreResources.getMouseSprite().draw(window);
	window.display();
}