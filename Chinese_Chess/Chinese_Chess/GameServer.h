#pragma once
#include <fstream>
#include <iostream>
#include "NetworkProtocol.h"
#include "GameHeader.h"
#include "Player.h"
struct RemotePeer
{
	RemotePeer();
	sf::TcpSocket socket;
	sf::Time lastPacketTime;
	Player player;
	bool ready;
	// If the peer did not send any data after n seconds, kick it out because something is wrong
	// The timedOut variable is just a flag that is set in the server logic to tell the handleDisconnections() function that this peer needs to be erased.
	bool timedOut;
};

typedef std::unique_ptr<RemotePeer> PeerPtr;

class GameServer
{
private:
	std::vector<PeerPtr> peerList;
	sf::TcpListener serverListener;
	unsigned int serverPort;
	bool listeningState;
	bool waitingThreadEnd;
	sf::Thread serverThread;
	int connectedPlayersNumber;
	int maxConnectedPlayers;
	sf::Clock serverClock;
	sf::Time clientTimeoutTime;

	bool serverTeamArr[2];

	void executionThread();
	void setListening(bool enable);
	void handleIncomingPackets();
	void handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& detectedTimeout);
	void handleIncomingConnections();
	void handlingDisconnections();	
	void updateLogic();
	void tick();
	void broadcastMessage(const std::string& message);
	sf::Time now() const;

public:
	GameServer();
	~GameServer();
};

