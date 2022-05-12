#pragma once
#include "GameHeader.h"

#include "Button.h"
#include "State.h"
class BlackIsCheckMate :
    public State
{
private:
    sf::RenderWindow* window;
    enum OptionNames
    {
        OK
    };
    std::vector<Button> mOptions;
    sf::Text text;
    sf::Text titleText;
    sf::RectangleShape backgroundRect;


public:
    BlackIsCheckMate(StateStack& _stack, StateContext _context);

private:
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;

};

