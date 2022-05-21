#include "GameMessage.h"

BlackIsCheckMate::BlackIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"�¤�Q�N�x");
}
RedIsCheckMate::RedIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"����Q�N�x");
}
BlackIsStalemate::BlackIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"�¤��� ����ӧQ");
}
bool BlackIsStalemate::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::OK) {
				requestStackPop();
				requestStackPush(States::ID::End);
			}
		}
	}
	return true;
}
RedIsStalemate::RedIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"������ �¤�ӧQ");
}

bool RedIsStalemate::handleEvent(const sf::Event& event)
{
	for (auto& button : mOptions) {
		button.handleEvent(*window);
		if (button.isPressed()) {
			if (button.getId() == OptionNames::OK) {
				requestStackPop();
				requestStackPush(States::ID::End);
			}
		}
	}
	return true;
}
