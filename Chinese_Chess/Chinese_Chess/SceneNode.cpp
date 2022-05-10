#include "SceneNode.h"

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//  states.transform contains the absolute world transform
	states.transform *= getTransform();
	drawCurrent(target, states);

	for (const auto& child : Children)
		(*child).draw(target, states);
}

SceneNode::SceneNode()
{
	Parent = nullptr;
}

void SceneNode::attachChild(SceneNodePtr child)
{
	child->Parent = this;
	Children.push_back(std::move(child));
}

SceneNode::SceneNodePtr SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(Children.begin(), Children.end(), 
		[&](SceneNodePtr& ptr) -> bool {
			return ptr.get() == &node;
		}
	);

	assert(found != Children.end());

	SceneNodePtr result = std::move(*found);
	result->Parent = nullptr;
	Children.erase(found);
	return result;
}
