#include "CoreResourceHolder.h"
#include <cassert>

int CoreResourceHolder::objectCounter = 0;

CoreResourceHolder::CoreResourceHolder(sf::RenderWindow& initWindowRef) :
	interfaceTextures{},
	gameTextures{},
	fonts{},
	windowRef{ initWindowRef },
	uiView{ sf::Vector2f{1920.f / 2, 1080.f / 2}, sf::Vector2f{ 1920.f, 1080.f } },
	mapView{ sf::Vector2f{1920.f / 2, 1080.f / 2}, sf::Vector2f{ 1920.f, 1080.f } },
	mouseOpticalReplacement{ initWindowRef, sf::Vector2i{64,64} }
{
	objectCounter++;
	assert(objectCounter == 1);

	loadInterfaceTextures();
	loadGameTextures();
	loadFonts();
	mouseOpticalReplacement.setAnimation(interfaceTextures.get("ManRunning"), 8, sf::seconds(1.f / 20));
}

void CoreResourceHolder::loadInterfaceTextures()
{
	interfaceTextures.add("CursorSword", "Media/Textures/Sword_Cursor.png");
	interfaceTextures.add("MainMenuStateBackground", "Media/Textures/MainMenu.png");

	interfaceTextures.add("GearNormal", "Media/Textures/Gear_notSelected.png");
	interfaceTextures.add("GearSelected", "Media/Textures/Gear_Selected.png");
	interfaceTextures.add("GreenBackground", "Media/Textures/GreenBackground.png");
	interfaceTextures.add("GreenButton", "Media/Textures/GreenButton.png");
	interfaceTextures.add("GreenButtonSelected", "Media/Textures/GreenButtonSelected.png");

	interfaceTextures.add("ManStand", "Media/Textures/Animations/StandStill.png");
	interfaceTextures.add("ManRunning", "Media/Textures/Animations/MoveLeft_512_64_8.png");

	interfaceTextures.add("128_1080", "Media/Textures/128_1080.png");
	interfaceTextures.add("1920_128", "Media/Textures/1920_128.png");
}

void CoreResourceHolder::loadGameTextures()
{
	gameTextures.add("TestGrass", "Media/Textures/GrassTile_32x32.png");
	gameTextures.add("TestWood", "Media/Textures/WoodTile_32x32.png");
}

void CoreResourceHolder::loadFonts()
{
	fonts.add("DieterSteffmann_MedivelFont", "Media/Fonts/Augusta.ttf");
}