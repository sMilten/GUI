#include "Tile.h"
#include <cassert>
#include <iostream>

Tile::Tile(sf::Vector2f initPos, int dummyForTileType) :
	centerPositionOnMap{ initPos },
	dummyType{ dummyForTileType }
{}

void Tile::zipBetweenVectorToBottom(Tile* neighbor, direction destinationDirection)
{

	if (destinationDirection == direction::TopCenter)
	{
		addTileToNeighbors(neighbor, destinationDirection);
		if (neighborTileMap.find(direction::MiddleLeft) != neighborTileMap.end())
		{
			neighborTileMap.at(direction::MiddleLeft)->addTileToNeighbors(neighbor, direction::TopRight);
		}
		if (neighborTileMap.find(direction::MiddleRight) != neighborTileMap.end())
		{
			neighborTileMap.at(direction::MiddleRight)->addTileToNeighbors(neighbor, direction::TopLeft);
		}
	}
	else if (destinationDirection == direction::BottomCenter)
	{
		addTileToNeighbors(neighbor, destinationDirection);
		if (neighborTileMap.find(direction::MiddleLeft) != neighborTileMap.end())
		{
			neighborTileMap.at(direction::MiddleLeft)->addTileToNeighbors(neighbor, direction::BottomRight);
		}
		if (neighborTileMap.find(direction::MiddleRight) != neighborTileMap.end())
		{
			neighborTileMap.at(direction::MiddleRight)->addTileToNeighbors(neighbor, direction::BottomLeft);
		}
		neighbor->zipBetweenVectorToBottom(this, direction::TopCenter);
	}
	else
	{
		assert(1 == 0);
	}
}

void Tile::setLeftNeighbor(Tile* neighbor)
{

	addTileToNeighbors(neighbor, direction::MiddleLeft);
	neighbor->addTileToNeighbors(this, direction::MiddleRight);
}

void Tile::addTileToNeighbors(Tile* neighbor, direction dirToSave)
{
	assert(neighbor != nullptr);
	neighborTileMap.insert(std::make_pair(dirToSave, neighbor));
}

void Tile::printNeighbors() const
{
	std::cout << "My Adress:\t" << this << " Pos: " << centerPositionOnMap.x << " " << centerPositionOnMap.y << std::endl;

	for (auto mapElement : neighborTileMap)
	{
		if (mapElement.first == direction::TopLeft)
			std::cout << "TopLeft\t\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::TopCenter)
			std::cout << "TopCenter\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::TopRight)
				std::cout << "TopRight\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::MiddleRight)
			std::cout << "MiddleRight\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::BottomRight)
			std::cout << "BottomRight\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::BottomCenter)
			std::cout << "BottomCenter\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::BottomLeft)
			std::cout << "BottomLeft\t: " << mapElement.second << "Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
		else if (mapElement.first == direction::MiddleLeft)
			std::cout << "MiddleLeft\t: " << mapElement.second << " Pos: " << mapElement.second->getPosition().x << " " << mapElement.second->getPosition().y << std::endl;
	}
}

void Tile::collectVisibleTiles(int width, int height, std::vector<std::vector<Tile*>>& visibleTiles)
{
	fillRows(width, height, visibleTiles);
}

void Tile::fillRows(int width, int& height, std::vector<std::vector<Tile*>>& visibleTiles)
{
	int realWidth = width;
	std::vector<Tile*> einNeuerVector{};
	height--;
	width--;
	einNeuerVector.push_back(this);
	neighborTileMap.at(direction::MiddleRight)->addTilesToVector(width, einNeuerVector);
	visibleTiles.push_back(einNeuerVector);
	if (height > 0)
	{
		neighborTileMap.at(direction::BottomCenter)->fillRows(realWidth, height, visibleTiles);
	}
}

void Tile::addTilesToVector(int& width, std::vector<Tile*>& vectorToFill)
{
	vectorToFill.push_back(this);
	width--;
	if (width > 0)
	{
		neighborTileMap.at(direction::MiddleRight)->addTilesToVector(width, vectorToFill);
	}
}