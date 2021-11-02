#include "ResourceHolder.h"

template<typename identifier, typename resource>
void ResourceHolder<typename identifier, typename resource>::add(const identifier& id, const sf::String& resourcePathName)
{
	std::unique_ptr<resource> newResource = std::make_unique<resource>();
	if (!newResource->loadFromFile(resourcePathName))
	{
		throw std::runtime_error("Das File " + resourcePathName + " ist nicht vorhanden!");
	}
	auto findTry = resourceMap.insert(std::make_pair(id, std::move(newResource)));
	assert(findTry.second);
}

template<typename identifier, typename resource>
template<typename parameterForFurtherRessources>
void ResourceHolder<typename identifier, typename resource>::add(const identifier& id, const sf::String& resourcePathName, parameterForFurtherRessources sP)
{
	std::unique_ptr<resource> uniqueRes = std::make_unique<resource>();
	if (!uniqueRes->loadFromFile(resourcePathName, sP))
	{
		throw std::runtime_error("Das File" + resourcePathName + "ist nicht vorhanden!");
	}
	auto findTry = resourceMap.insert(std::make_pair(id, std::move(uniqueRes)));
	assert(findTry.second);
}

template<typename identifier, typename resource>
const resource& ResourceHolder<typename identifier, typename resource>::get(identifier id) const
{
	auto foundPair = resourceMap.find(id);

	assert(foundPair != resourceMap.end());
	return *foundPair->second;
}