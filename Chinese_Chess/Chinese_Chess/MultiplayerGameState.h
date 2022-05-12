#pragma once
#include "fstream"
#include "Button.h"
#include "NetworkProtocol.h"
#include "GameHeader.h"
#include "Board.h"
#include "State.h"
class MultiplayerGameState
	: public State
{
	enum class MutiplayerStatus
	{
		connecting,
		waitingInit,
		Ready,
		WaitClientPressed,
		WaitClientPathPressed,
		WaitRemotePressed,
		WaitRemotePathPressed,
		End,
	};
private:
	sf::RenderWindow* window;
	Board localBoard;
	Player LocalPlayer;
	Player RemotePlayer;
	bool isInit;
	bool isReady;
	bool isConnected;
	sf::IpAddress serverIp;
	sf::TcpSocket clientSocket;
	sf::Clock localClock;
	MutiplayerStatus localStatus;

	sf::RectangleShape background;

private:
	class ConnectingState
		: public State
	{
	private:
		sf::RenderWindow* window;
		enum OptionNames
		{
			Exit,
		};
		std::vector<Button> mOptions;
		sf::Text text;
		sf::Text titleText;
		sf::RectangleShape backgroundRect;

	public:
		ConnectingState(StateStack& _stack, StateContext _context);
		virtual void draw() override;
		virtual bool update(sf::Time dt) override;
		virtual bool handleEvent(const sf::Event& event) override;
	};

public:
	MultiplayerGameState(StateStack& _stack, StateContext _context);
	virtual void draw() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;

	void handleIncomingPackets();
	sf::Time now() const;

};


