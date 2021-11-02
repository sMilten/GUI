#include "World.h"
#include <cassert>

int World::objCounter = 0;

World::World(CoreResourceHolder& initResourceHolder) :
	coreResourcesRef{initResourceHolder},
	map{ initResourceHolder }
{
	objCounter++;
	assert(objCounter == 1);
}

World::~World()
{
	objCounter--;
}

void World::update(sf::Time dt)
{
	sf::Vector2f upperLeftCoordsInPx = coreResourcesRef.getMapView().getCenter() - (coreResourcesRef.getMapView().getSize() / 2.f);
	//std::cout << "UpperLeft\tx: " << upperLeftCoordsInPx.x << ", y: " << upperLeftCoordsInPx.y << std::endl;
	map.update(upperLeftCoordsInPx);
}
void World::draw(sf::RenderWindow& window)
{
	map.draw(window);
}

void World::initWorld(sf::Vector2f initTileSize, sf::Vector2i initTileNumber, sf::FloatRect activeGameViewForCorrection)
{

	sf::Vector2i numberOfVisibleTiles{ coreResourcesRef.getMapView().getSize() };
	numberOfVisibleTiles.x = numberOfVisibleTiles.x / static_cast<int>(initTileSize.x) + 1;
	numberOfVisibleTiles.y = numberOfVisibleTiles.y / static_cast<int>(initTileSize.y) + 1;
	sf::Vector2f drawOffset{ activeGameViewForCorrection.left, activeGameViewForCorrection.top };
	assert(numberOfVisibleTiles.x <= initTileNumber.x && numberOfVisibleTiles.y <= initTileNumber.y);

	map.initMap(initTileSize, initTileNumber, numberOfVisibleTiles, drawOffset);
}

void World::destroyWorld()
{

}