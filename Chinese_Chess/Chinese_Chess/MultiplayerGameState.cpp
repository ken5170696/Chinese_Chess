#include "MultiplayerGameState.h"


MultiplayerGameState::MultiplayerGameState(StateStack& _stack, StateContext _context)
    : State(_stack, _context)
{
}

void MultiplayerGameState::draw()
{
}

bool MultiplayerGameState::update(sf::Time dt)
{
    return false;
}

bool MultiplayerGameState::handleEvent(const sf::Event& event)
{
    return false;
}
