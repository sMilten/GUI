#pragma once
#include <SFML/Graphics.hpp>
#include "CoreResourceHolder.h"
#include "Tile.h"

class Map final : sf::NonCopyable
{
	static int objCounter;
public:
	Map(CoreResourceHolder& initResourceHolder);
	~Map();
	void initMap(sf::Vector2f initTileSize, sf::Vector2i initTileNumber, sf::Vector2i initNumberOfVisibleTiles, sf::Vector2f initdrawOffset);
	void destroyWorld();
	void update(sf::Vector2f upperLeftScreenpointInPx);
	void draw(sf::RenderWindow& window);

private:
	sf::Vector2i numberofVisibleTiles;
	sf::Vector2f drawOffset;
	sf::Vector2f tileSize;
	std::vector<std::vector<Tile*>> allTiles;
	std::vector<std::vector<Tile*>> visibleTiles;

	sf::Vector2f currentPositionInTiles;
	sf::Time timeBetweenUpdates;
	sf::Time elapsedTime;

	CoreResourceHolder& coreResourcesRef;
	sf::Sprite testSprite;
};

