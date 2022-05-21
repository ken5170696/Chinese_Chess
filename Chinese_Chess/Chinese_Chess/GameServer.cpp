#include "GameServer.h"

// This is the Server Thread!
void GameServer::executionThread()
{
	std::cout << "Server Log: Server Thread Started!\n";
	// initialize
	setListening(true);

	// updateLogic more often
	sf::Time stepInterval = sf::seconds(1.f / 60.f);
	sf::Time stepTime = sf::Time::Zero;
	sf::Time tickInterval = sf::seconds(1.f / 20.f);
	sf::Time tickTime = sf::Time::Zero;
	sf::Clock stepClock, tickClock;


	// server loop
	while (!waitingThreadEnd)
	{
		// handle all incoming traffic from the connected peers
		handleIncomingPackets();

		// accept new connections
		handleIncomingConnections();

		stepTime += stepClock.getElapsedTime();
		stepClock.restart();

		tickTime += tickClock.getElapsedTime();
		tickClock.restart();

		// Fixed update step
		while (stepTime >= stepInterval)
		{
			// update server data
			updateLogic();
			stepTime -= stepInterval;
		}

		// Fixed tick step
		while (tickTime >= tickInterval)
		{
			// send a snapshot of the server's state to the clients
			tick();
			tickTime -= tickInterval;
		}
		sf::sleep(sf::milliseconds(50));
	}
}

void GameServer::setListening(bool enable)
{
	// Check if it isn't already listening
	if (enable)
	{
		if (!listeningState)
			listeningState = (serverListener.listen(serverPort) == sf::TcpListener::Done);
	}
	else
	{
		serverListener.close();
		listeningState = false;
	}
}

void GameServer::handleIncomingPackets()
{
	bool detectedTimeout = false;

	for(auto& peer : peerList)
	{
		if (peer->ready)
		{
			sf::Packet packet;
			while (peer->socket.receive(packet) == sf::Socket::Done)
			{
				// Interpret packet and react to it
				handleIncomingPacket(packet, *peer, detectedTimeout);

				// Packet was indeed received, update the ping timer
				peer->lastPacketTime = now();
				packet.clear();
			}

			if (now() >= peer->lastPacketTime + clientTimeoutTime)
			{
				peer->timedOut = true;
				detectedTimeout = true;
			}
		}
	}
	if (detectedTimeout)
		handlingDisconnections();

}

void GameServer::handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& detectedTimeout)
{
	sf::Int32 packetType;
	packet >> packetType;
}

void GameServer::handleIncomingConnections()
{
	// reject all the connection when listeningState is false
	if (!listeningState)
		return;

	// someone try to connect when serverListener.accept() == sf::TcpListener::Done
	if (serverListener.accept(peerList[connectedPlayersNumber]->socket) == sf::TcpListener::Done)
	{
		std::cout << peerList[connectedPlayersNumber]->socket.getRemoteAddress() << " : connected!\n";
		sf::Packet packet;
		/* Sending information to client*/
		packet << static_cast<sf::Int32>(Server::PacketType::InitialState);
		// send Team
		if (connectedPlayersNumber == 0) {
			Player tmpPlayer(Team::Black);
			peerList[connectedPlayersNumber]->player = tmpPlayer;
			packet << static_cast<sf::Int32>(Team::Black);
			peerList[connectedPlayersNumber]->socket.send(packet);

		}else {
			Player tmpPlayer(Team::Red);
			peerList[connectedPlayersNumber]->player = tmpPlayer;
			packet << static_cast<sf::Int32>(Team::Red);
			peerList[connectedPlayersNumber]->socket.send(packet);
			packet.clear();

			packet << static_cast<sf::Int32>(Server::PacketType::InitialRemotePlayer);
			packet << static_cast<sf::Int32>(Team::Black);
			peerList[connectedPlayersNumber]->socket.send(packet);

			sf::Packet oldPlayerpacket;
			oldPlayerpacket << static_cast<sf::Int32>(Server::PacketType::InitialRemotePlayer);
			oldPlayerpacket << static_cast<sf::Int32>(Team::Red);
			peerList[0]->socket.send(oldPlayerpacket);

		}

		peerList[connectedPlayersNumber]->ready = true;
		peerList[connectedPlayersNumber]->lastPacketTime = now(); // prevent initial timeouts
		connectedPlayersNumber++;

		if (connectedPlayersNumber >= maxConnectedPlayers)
			setListening(false);
		else {
			// Add a new waiting peer
			peerList.push_back(PeerPtr(new RemotePeer()));
		}
	}
}

void GameServer::handlingDisconnections()
{
	for (auto peerItr = peerList.begin(); peerItr != peerList.end(); )
	{
		if (connectedPlayersNumber &&(*peerItr)->timedOut)
		{
			std::cout << (*peerItr)->socket.getRemoteAddress() << " : Dissconnected\n";
			connectedPlayersNumber--;
			peerItr = peerList.erase(peerItr);

			// Go back to a listening state if needed
			if (connectedPlayersNumber < maxConnectedPlayers)
			{
				peerList.push_back(PeerPtr(new RemotePeer()));
				setListening(true);
			}

			broadcastMessage("An ally has disconnected.");
			break;
		}
		else {
			peerItr++;
		}
	}
	
}

void GameServer::updateLogic()
{
	Player playerBlack, playerRed;
	if (connectedPlayersNumber == 1)
		playerBlack = peerList[0]->player;
	if (connectedPlayersNumber == 1)
		playerRed = peerList[1]->player;

	board.update(playerBlack.getChessList(), playerRed.getChessList());
}

void GameServer::tick()
{
}

void GameServer::broadcastMessage(const std::string& message)
{
	for (std::size_t i = 0; i < connectedPlayersNumber; ++i)
	{
		if (peerList[i]->ready)
		{
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Server::PacketType::BroadcastMessage);
			packet << message;

			peerList[i]->socket.send(packet);
		}
	}
}

sf::Time GameServer::now() const
{

	return serverClock.getElapsedTime();
}

GameServer::GameServer()
	:peerList(1),
	board(),
	serverThread(&GameServer::executionThread, this)
{
	std::cout << "Server Log: Server Started!\n";
	serverListener.setBlocking(false);
	serverPort = SERVER_POST;     
	listeningState = false;
	waitingThreadEnd = false;
	connectedPlayersNumber = 0;
	maxConnectedPlayers = MAXPLAYER;
	peerList[0].reset(new RemotePeer());
	peerList[0]->ready = false;
	clientTimeoutTime = sf::seconds(CLIENT_TIMEOUT_TIME);

	std::fstream ipFile;
	ipFile.open(IPFILE, std::ios_base::out);
	if (!ipFile)
	{
		std::cerr << "Server Log: Can't open file!\n";
	}
	ipFile << sf::IpAddress::getLocalAddress().toString();
	ipFile.close();

	// Starting the server
	std::cout << "Server Log: Initialize finished, now start server thread.\n";
	serverThread.launch();
}

GameServer::~GameServer()
{
	bool fileStatus = std::remove(IPFILE);
	if(fileStatus)

	waitingThreadEnd = true;
	serverThread.wait();
}

RemotePeer::RemotePeer()
	: player(Team::Black)
{
	socket.setBlocking(false);
	ready = false;
	timedOut = false;
}
