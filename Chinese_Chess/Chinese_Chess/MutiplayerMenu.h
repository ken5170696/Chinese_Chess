#pragma once
#include <fstream>
#include "GameServer.h"
#include "NetworkProtocol.h"
#include "Button.h"
#include "TextBox.h"
#include "GameHeader.h"
#include "State.h"

class MutiplayerMenu
	: public State
{
private:
	sf::RenderWindow* window;
	enum OptionNames
	{
		Host,
		Client,
		Exit,
	};
	std::vector<Button> mOptions;
	sf::Text text;
	sf::Text titleText;
	sf::RectangleShape backgroundRect;
	std::unique_ptr<GameServer> gs;
public:
	MutiplayerMenu(StateStack& _stack, StateContext _context);
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

};

class ServerEnterIpMenu
	: public State
{
private:
	sf::RenderWindow* window;
	enum OptionNames
	{
		Submit,
		Exit,
	};
	std::vector<Button> mOptions;
	TextBox* ipTextBox;
	sf::Text titleText;
	sf::RectangleShape backgroundRect;

public:
	ServerEnterIpMenu(StateStack& _stack, StateContext _context);
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

};