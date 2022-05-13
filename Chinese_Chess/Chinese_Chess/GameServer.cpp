#include "GameServer.h"

// This is the Server Thread!
void GameServer::executionThread()
{
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

		peerList[connectedPlayersNumber]->socket.send(packet);
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
			packet << static_cast<sf::Int32>(Server::BroadcastMessage);
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
	serverThread(&GameServer::executionThread, this)
{
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
		std::cerr << "Can't open file!\n";
	}
	ipFile << sf::IpAddress::getLocalAddress().toString();
	ipFile.close();

	// Starting the server
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
