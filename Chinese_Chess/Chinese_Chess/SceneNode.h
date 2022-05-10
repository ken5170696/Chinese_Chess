#pragma once
#include "GameHeader.h"
#include <iostream>
#include <vector>
#include <assert.h>
/* scene graph */
class SceneNode
	: public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> SceneNodePtr;

private:
	std::vector<SceneNodePtr> Children;
	SceneNode* Parent;

private:
	/* "RenderWindow" class internally calls our draw() */
	virtual void draw(sf::RenderTarget& target , sf::RenderStates states) const override;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	SceneNode();
	void attachChild(SceneNodePtr child);
	SceneNodePtr detachChild(const SceneNode& node);

};

