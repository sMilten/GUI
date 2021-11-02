#pragma once
#include <SFML/Graphics.hpp>

#include "StateHandler.h"
#include "MouseSprite.h"
#include "ResourceHolder.h"
#include "CoreResourceHolder.h"

class Engine final : sf::NonCopyable
{
	static int objectCounter;
	static float screenWidth;
	static float screenHeight;
	static float ticksPerSecond;

public:
	Engine();
	~Engine();
	void run();

private:

	void handleInput();
	void update(sf::Time dt);
	void draw();

	sf::Clock clk;
	sf::Time dt;
	sf::Time tickLenght;

	StateHandler stateHandler;
	CoreResourceHolder coreResources;

	sf::RenderWindow window;
};

