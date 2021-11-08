#include "Map.h"
#include <cassert>
#include <cmath>

int Map::objCounter = 0;

Map::Map(CoreResourceHolder& initResourceHolder) :
	coreResourcesRef{ initResourceHolder },
	numberofVisibleTiles{},
	drawOffset{},
	allTiles{},
	visibleTiles{},
	tileSize{},
	timeBetweenUpdates{ sf::seconds(1 / 20.f) },
	elapsedTime{ sf::Time::Zero },
	testSprite{ coreResourcesRef.getGameTexture("TestGrass") },
	currentPositionInTiles{ -10,-10 }
{
	objCounter++;
	assert(objCounter == 1);
	testSprite.setPosition(-100, -100);
}

Map::~Map()
{
	objCounter--;
	for (auto& vec : allTiles)
	{
		for (std::size_t i = 0; i < vec.size(); i++)
		{
			delete vec[i];
			vec[i] = nullptr;
		}
	}
}

void Map::initMap(sf::Vector2f initTileSize, sf::Vector2i initTileNumber, sf::Vector2i initNumberOfVisibleTiles, sf::Vector2f initdrawOffset)
{
	numberofVisibleTiles = initNumberOfVisibleTiles;
	drawOffset = initdrawOffset;
	tileSize = initTileSize;

	for (int numberOfVectors = 0; numberOfVectors != initTileNumber.x; numberOfVectors++)
	{
		std::vector<Tile*> einNeuerVector{};
		for (int numberOfTile = 0; numberOfTile != initTileNumber.y; numberOfTile++)
		{
			Tile* einNeuerTile = new Tile{ sf::Vector2f{numberOfTile * tileSize.x, numberOfVectors * tileSize.y}, 99 };

			if (numberOfTile > 0)
			{
				einNeuerTile->setLeftNeighbor(einNeuerVector.back());
			}
			einNeuerVector.push_back(einNeuerTile);
		}
		// Hier noch die "Reisverschluss"-verbindung!
		if (numberOfVectors > 0)
		{
			auto tileInOldVector = allTiles.back().begin();
			for (auto tileInCurrentVector : einNeuerVector)
			{
				(*tileInOldVector)->zipBetweenVectorToBottom(tileInCurrentVector, Tile::direction::BottomCenter);
				tileInOldVector++;
			}
		}
		allTiles.push_back(einNeuerVector);
	}
}

void Map::destroyWorld()
{

}

void Map::update(sf::Vector2f upperLeftScreenpointInPx)
{
	sf::Vector2f upperLeftPositionInTiles{ floor(upperLeftScreenpointInPx.x / tileSize.x), floor(upperLeftScreenpointInPx.y / tileSize.y) };
	if (upperLeftPositionInTiles.x != currentPositionInTiles.x || upperLeftPositionInTiles.y != currentPositionInTiles.y)
	{
		currentPositionInTiles = upperLeftPositionInTiles;
		Tile* upperLeft = allTiles.at(static_cast<int>(currentPositionInTiles.y)).at(static_cast<int>(currentPositionInTiles.x));
		visibleTiles.clear();
		upperLeft->collectVisibleTiles(numberofVisibleTiles.x, numberofVisibleTiles.y, visibleTiles);
		testSprite.setPosition(upperLeft->getPosition().x+drawOffset.x, upperLeft->getPosition().y+drawOffset.y);
	}
}

void Map::draw(sf::RenderWindow& window)
{
	window.draw(testSprite);
}
