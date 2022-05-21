#include "GameMessage.h"

BlackIsCheckMate::BlackIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"黑方被將軍");
}
RedIsCheckMate::RedIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"紅方被將軍");
}
BlackIsStalemate::BlackIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	setTitle(L"黑方欠行 紅方勝利");
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
	setTitle(L"紅方欠行 黑方勝利");
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
