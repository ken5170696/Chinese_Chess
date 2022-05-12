#pragma once
#include "Button.h"
#include "State.h"
class MessageBox :
    public State
{
protected:
    sf::RenderWindow* window;
    enum OptionNames
    {
        OK,
    };
    std::vector<Button> mOptions;
    sf::Text titleText;
    sf::RectangleShape backgroundRect;


public:
    MessageBox(StateStack& _stack, StateContext _context);

protected:
    void setTitle(const std::string& titleString);
    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;
};

