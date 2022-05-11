#pragma once

#define SERVER_POST 8787
#define MAXPLAYER 2
#define CLIENT_TIMEOUT_TIME 3.f // second
#define IPFILE "serverAddr.txt"

namespace Server
{
	// Packets originated in the server
	// format: [Int32:packetType]
	enum PacketType
	{
		/*
			This takes a std::stringand is used to send a message
			to all clients, which they would show on the screen for some seconds.
		*/
		BroadcastMessage,	// format: [Int32:packetType] [string:message]
		InitialState,
		PlayerEvent,
		PlayerRealtimeChange,
		PlayerConnect,
		PlayerDisconnect,
		UpdateClientState,
	};
}

namespace Client
{
	// Packets originated in the client
	enum PacketType
	{
		PlayerEvent,
		PlayerRealtimeChange,
		RequestCoopPartner,
		PositionUpdate,
		GameEvent,
		Quit
	};
}