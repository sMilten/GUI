#pragma once
#include <SFML/Graphics.hpp>
#include "CoreResourceHolder.h"
#include "Map.h"

class World final : public sf::NonCopyable
{
	static int objCounter;

public:
	World(CoreResourceHolder& initResourceHolder);
	~World();
	void update(sf::Time dt);
	void draw(sf::RenderWindow& window);
	void initWorld(sf::Vector2f initTileSize, sf::Vector2i initTileNumber, sf::FloatRect activeGameViewForCorrection);
	void destroyWorld();

private:
	Map map;
	CoreResourceHolder& coreResourcesRef;
};

