#pragma once
#include <SFML/Graphics.hpp>

#include <functional>
#define DISTANCE_TO_SCREEN_BOUNDRY 2	// we dont want to see the edges of the tiles

class ScreenScroller
{
public:
	ScreenScroller(sf::View& initMapView);

	enum class ViewMovmentDirection
	{
		Up,
		Down,
		Left,
		Right
	};
	void addMoveOrderForUpdate(ViewMovmentDirection giveDir);
	

	void setScrollSpeed(sf::Vector2f newSpeed);
	void initMapInPx(sf::Vector2f initMapSizePx);
	void update(sf::Time dt);

private:

	void handleVerticalMovment(ViewMovmentDirection giveDir);
	void addUpMoveOrder();
	void addDownMoveOrder();
	void handleHorizontalMovment(ViewMovmentDirection giveDir);
	void addLeftMoveOrder();
	void addRightMoveOrder();

	sf::View& mapView;

	std::vector<std::function<void(sf::Time dt)>> movmentOrders;
	bool horizontalDone;
	bool verticalDone;
	sf::Vector2f scrollSpeed;
	sf::Vector2f mapSizeInPx;

};

