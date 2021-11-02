#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>

template<typename identifier, typename resource>
class ResourceHolder
{
public:
	void add(const identifier& id, const sf::String& resourcePathName);
	template<typename parameterForFurtherRessources>
	void add(const identifier& id, const sf::String& resourcePathName, parameterForFurtherRessources sP);
	const resource& get(identifier id) const;

private:
	std::map<identifier, std::unique_ptr<resource>> resourceMap;
};