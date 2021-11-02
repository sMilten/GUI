#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceHolder.h"
#include "MouseSprite.h"

class CoreResourceHolder final : public sf::NonCopyable
{
	typedef ResourceHolder<sf::String, sf::Texture> textureHolder;
	typedef ResourceHolder<sf::String, sf::Font> fontHolder;
	static int objectCounter;

public:
	CoreResourceHolder(sf::RenderWindow& windowRef);

	inline const sf::Texture& getInterfaceTexture(const sf::String& textureName) const {
		return interfaceTextures.get(textureName);
	}

	inline const sf::Texture& getGameTexture(const sf::String& textureName) const {
		return gameTextures.get(textureName);
	}

	inline const sf::Font& getFont(const sf::String& textureName) const {
		return fonts.get(textureName);
	}

	inline const sf::View& getUIView() const {
		return uiView;
	}

	inline sf::View& getMapView() {
		return mapView;
	}

	inline sf::RenderWindow& getWindow() {
		return windowRef;
	}

	inline MouseSprite& getMouseSprite() {
		return mouseOpticalReplacement;
	}

private:

	void loadInterfaceTextures();
	void loadGameTextures();
	void loadFonts();

	ResourceHolder<sf::String, sf::Texture> interfaceTextures;
	ResourceHolder<sf::String, sf::Texture> gameTextures;
	ResourceHolder<sf::String, sf::Font> fonts;

	sf::RenderWindow& windowRef;
	sf::View uiView;
	sf::View mapView;

	MouseSprite mouseOpticalReplacement;
};