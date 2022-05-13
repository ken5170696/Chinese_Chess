#include "GameMessage.h"

BlackIsCheckMate::BlackIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"�¤�Q�N�x");
}
RedIsCheckMate::RedIsCheckMate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"����Q�N�x");
}
BlackIsStalemate::BlackIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{

	titleText.setString(L"�¤���");
}
RedIsStalemate::RedIsStalemate(StateStack& _stack, StateContext _context)
	: MessageBox(_stack, _context)
{
	titleText.setString(L"������");
}