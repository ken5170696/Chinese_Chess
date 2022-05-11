#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
// remove comment to disable assert.h
// #define NDEBUG
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;

public:
	void load(Identifier id, const std::string& filename) {
		std::unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("TextureHolder::load - Failed to load " + filename);

		auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
		assert(inserted.second);
	};
	Resource& get(Identifier id)
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return *found->second;
	};
	const Resource& get(Identifier id) const
	{
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());

		return *found->second;
	};
};
