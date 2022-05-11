#pragma once
#include "State.h"
class TitleState : public State
{
public:
	TitleState(StateStack& stack, StateContext context);
	virtual void draw();
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
private:
	sf::Sprite mBackgroundSprite;
	sf::Text mText;
	bool mShowText;
	sf::Time mTextEffectTime;
};

