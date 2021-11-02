#pragma once
#include <SFML/Graphics.hpp>

class Tile
{

public:

	enum class direction
	{
		TopLeft,
		TopCenter,
		TopRight,
		MiddleRight,
		BottomRight,
		BottomCenter,
		BottomLeft,
		MiddleLeft
	};

	Tile(sf::Vector2f initPos, int dummyForTileType);
	void setLeftNeighbor(Tile* neighbor);
	void zipBetweenVectorToBottom(Tile* neighbor, direction dirToSave);
	void printNeighbors() const;
	inline sf::Vector2f getPosition() const {
		return centerPositionOnMap;
	}
	inline int getType() const {
		return dummyType;
	}
	void collectVisibleTiles(int width, int height, std::vector<std::vector<Tile*>>& visibleTiles);

private:

	void addTileToNeighbors(Tile* neighbor, direction dirToSave);

	void fillRows(int width, int& height, std::vector<std::vector<Tile*>>& visibleTiles);
	void addTilesToVector(int& width, std::vector<Tile*>& vectorToFill);

	sf::Vector2f centerPositionOnMap;
	std::map<direction, Tile*> neighborTileMap;
	int dummyType;
};

