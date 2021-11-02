#include "ScreenScroller.h"
#include <cassert>

ScreenScroller::ScreenScroller(sf::View& initMapView) :
	mapView{ initMapView },
	scrollSpeed{ 400,400 },
	movmentOrders{},
	horizontalDone{ false },
	verticalDone{ false }
{
	mapView.setCenter(DISTANCE_TO_SCREEN_BOUNDRY + mapView.getSize().x / 2.f, DISTANCE_TO_SCREEN_BOUNDRY + mapView.getSize().y / 2.f);
	initMapInPx(sf::Vector2f{ 2000, 2000 });
}

void ScreenScroller::setScrollSpeed(sf::Vector2f newSpeed)
{
	scrollSpeed = newSpeed;
}

void ScreenScroller::initMapInPx(sf::Vector2f initMapSizePx)
{
	mapView.setCenter(DISTANCE_TO_SCREEN_BOUNDRY + mapView.getSize().x / 2.f, DISTANCE_TO_SCREEN_BOUNDRY + mapView.getSize().y / 2.f);
	mapSizeInPx = initMapSizePx;
}

void ScreenScroller::update(sf::Time dt)
{
	// 30 FPS ist ganz gut.
	// Geschwindigkeit und FPS sind wichtig! -> bei 60 FPS: interner Zähler mit 30 FPS? -> Flackern verhindern?
	for (auto itVec : movmentOrders)
	{
		itVec(dt);
	}
	horizontalDone = false;
	verticalDone = false;
	movmentOrders.clear();
}

void ScreenScroller::addMoveOrderForUpdate(ViewMovmentDirection giveDir)
{
	if (verticalDone == false)
		handleVerticalMovment(giveDir);
	if(horizontalDone == false)
		handleHorizontalMovment(giveDir);
}

void ScreenScroller::handleVerticalMovment(ViewMovmentDirection giveDir)
{
	if (giveDir == ViewMovmentDirection::Up || giveDir == ViewMovmentDirection::Down)
	{
		verticalDone = true;
		if (giveDir == ViewMovmentDirection::Up)
		{
			addUpMoveOrder();
		}

		else
		{
			addDownMoveOrder();
		}
	}
}

void ScreenScroller::addUpMoveOrder()
{
	movmentOrders.push_back([this](sf::Time dt)
		{
			float screenBoundry = mapView.getCenter().y - mapView.getSize().y / 2.f - scrollSpeed.y * dt.asSeconds();
			if (screenBoundry > DISTANCE_TO_SCREEN_BOUNDRY)
			{
				this->mapView.setCenter(mapView.getCenter().x, mapView.getCenter().y - scrollSpeed.y * dt.asSeconds());
			}
			else
			{
				this->mapView.setCenter(mapView.getCenter().x, mapView.getSize().y / 2.f + DISTANCE_TO_SCREEN_BOUNDRY);
			}
		}
	);
}

void ScreenScroller::addDownMoveOrder()
{
	movmentOrders.push_back([this](sf::Time dt)
		{
			float screenBoundry = mapView.getCenter().y + mapView.getSize().y / 2.f + scrollSpeed.y * dt.asSeconds();
			if (screenBoundry < mapSizeInPx.y - DISTANCE_TO_SCREEN_BOUNDRY)
			{
				this->mapView.setCenter(mapView.getCenter().x, mapView.getCenter().y + scrollSpeed.y * dt.asSeconds());
			}
			else
			{
				this->mapView.setCenter(mapView.getCenter().x, mapSizeInPx.y - mapView.getSize().y / 2.f - DISTANCE_TO_SCREEN_BOUNDRY);
			}
		}
	);
}

void ScreenScroller::handleHorizontalMovment(ViewMovmentDirection giveDir)
{
	if (giveDir == ViewMovmentDirection::Left || giveDir == ViewMovmentDirection::Right)
	{
		horizontalDone = true;
		if (giveDir == ViewMovmentDirection::Left)
		{
			addLeftMoveOrder();
		}

		else
		{
			addRightMoveOrder();
		}
	}
}

void ScreenScroller::addLeftMoveOrder()
{
	movmentOrders.push_back(
		[this](sf::Time dt) {
			float screenBoundry = mapView.getCenter().x - mapView.getSize().x / 2.f - scrollSpeed.x * dt.asSeconds();
			if (screenBoundry > DISTANCE_TO_SCREEN_BOUNDRY)
			{
				this->mapView.setCenter(mapView.getCenter().x - scrollSpeed.x * dt.asSeconds(), mapView.getCenter().y);
			}
			else
			{
				this->mapView.setCenter(mapView.getSize().x / 2.f + DISTANCE_TO_SCREEN_BOUNDRY, mapView.getCenter().y);
			}
		}
	);
}

void ScreenScroller::addRightMoveOrder()
{
	movmentOrders.push_back(
		[this](sf::Time dt) {
			float screenBoundry = mapView.getCenter().x + mapView.getSize().x / 2.f + scrollSpeed.x * dt.asSeconds();
			if (screenBoundry < mapSizeInPx.x - DISTANCE_TO_SCREEN_BOUNDRY)
			{
				this->mapView.setCenter(mapView.getCenter().x + scrollSpeed.x * dt.asSeconds(), mapView.getCenter().y);
			}
			else
			{
				this->mapView.setCenter(mapSizeInPx.x - mapView.getSize().x / 2.f - DISTANCE_TO_SCREEN_BOUNDRY, mapView.getCenter().y);
			}
		}
	);
}