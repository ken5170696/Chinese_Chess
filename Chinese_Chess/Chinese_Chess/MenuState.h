#pragma once
#include "MenuView.h"
#include "Button.h"
#include "State.h"
class MenuState : public State
{
private:
    sf::RenderWindow* window;
    enum OptionNames
    {
        Play,
        Multplayer,
        Exit,
    };
    std::vector<Button> mOptions;
    sf::Text text;
    sf::Text titleText;
    sf::RectangleShape backgroundRect;
    MenuView menuView;

public:
    MenuState(StateStack& _stack, StateContext _context);

private:
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;
};

