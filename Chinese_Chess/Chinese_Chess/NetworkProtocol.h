#pragma once

#define SERVER_POST 8787
#define MAXPLAYER 2
#define CLIENT_TIMEOUT_TIME 3.f // second
#define IPFILE "serverAddr.txt"

namespace Server
{
	// Packets originated in the server
	// format: [Int32:packetType]
	enum class PacketType
	{
		/*
			This takes a std::stringand is used to send a message
			to all clients, which they would show on the screen for some seconds.
		*/
		BroadcastMessage,	// format: [Int32:packetType] [string:message]
		InitialState,
		InitialRemotePlayer,
		PlayerDisconnect,
		RemotePlayerDisconnect,
		RemotePlayerQuit,
	};
}


struct ServerCommand
{
	Server::PacketType packetType;

};

namespace Client
{
	// Packets originated in the client
	enum class PacketType
	{
		PlayerEvent,
		PlayerRealtimeChange,
		GameEvent,
		Quit,
		None
	};
}