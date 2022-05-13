#pragma once
#include "GameHeader.h"
#include "MessageBox.h"
#include "Button.h"
#include "State.h"
class BlackIsCheckMate : public MessageBox
{
public:
    BlackIsCheckMate(StateStack& _stack, StateContext _context);
};
class BlackIsStalemate : public MessageBox
{
public:
    BlackIsStalemate(StateStack& _stack, StateContext _context);
};
class RedIsCheckMate : public MessageBox
{
public:
    RedIsCheckMate(StateStack& _stack, StateContext _context);
};
class RedIsStalemate : public MessageBox
{
public:
    RedIsStalemate(StateStack& _stack, StateContext _context);
};
