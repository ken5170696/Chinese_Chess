#include "GameMessage.h"

BlackIsCheckMate::BlackIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"黑方被將軍");
}
RedIsCheckMate::RedIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"紅方被將軍");
}
BlackIsStalemate::BlackIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{

	titleText.setString(L"黑方欠行");
}
RedIsStalemate::RedIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"紅方欠行");
}