#pragma once
#include "GameHeader.h"
// remove comment to disable assert.h
// #define NDEBUG
#include <assert.h>
#include <map>

namespace Textures
{
	enum class ID {
		Chess_King_Red,
		Chess_Advisors_Red,
		Chess_Minister_Red,
		Chess_Chariots_Red,
		Chess_Knights_Red,
		Chess_Cannons_Red,
		Chess_Soldiers_Red,

		Chess_King_Black,
		Chess_Advisors_Black,
		Chess_Minister_Black,
		Chess_Chariots_Black,
		Chess_Knights_Black,
		Chess_Cannons_Black,
		Chess_Soldiers_Black,

		CheckBoard
	};
}
template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
	std::map<Identifier, std::unique_ptr<sf::Texture>> mResourceMap;

public:
	void load(Identifier id, const std::string& filename);
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
};
	
