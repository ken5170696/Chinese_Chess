#pragma once
#include "ResourceHolder.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define CHESS_KING_BLACK_IMG     "./Asset/Image/Chess/Chess_King_Black.png"
#define CHESS_ADVISORS_BLACK_IMG "./Asset/Image/Chess/Chess_Advisors_Black.png"
#define CHESS_MINISTER_BLACK_IMG "./Asset/Image/Chess/Chess_Minister_Black.png"
#define CHESS_CHARIOTS_BLACK_IMG "./Asset/Image/Chess/Chess_Chariots_Black.png"
#define CHESS_KNIGHTS_BLACK_IMG  "./Asset/Image/Chess/Chess_Knights_Black.png"
#define CHESS_CANNONS_BLACK_IMG  "./Asset/Image/Chess/Chess_Cannons_Black.png"
#define CHESS_SOLDIERS_BLACK_IMG "./Asset/Image/Chess/Chess_Soldiers_Black.png"

#define CHESS_KING_RED_IMG     "./Asset/Image/Chess/Chess_King_Red.png"
#define CHESS_ADVISORS_RED_IMG "./Asset/Image/Chess/Chess_Advisors_Red.png"
#define CHESS_MINISTER_RED_IMG "./Asset/Image/Chess/Chess_Minister_Red.png"
#define CHESS_CHARIOTS_RED_IMG "./Asset/Image/Chess/Chess_Chariots_Red.png"
#define CHESS_KNIGHTS_RED_IMG  "./Asset/Image/Chess/Chess_Knights_Red.png"
#define CHESS_CANNONS_RED_IMG  "./Asset/Image/Chess/Chess_Cannons_Red.png"
#define CHESS_SOLDIERS_RED_IMG "./Asset/Image/Chess/Chess_Soldiers_Red.png"

#define CHECKBOARD_IMG "./Asset/Image/Checkboard/Checkboard.jpg"

#define FONT_FILE_PATH "./Asset/font/º–∑¢≈È.ttc"

#define WINDOW_RESOLUTION_WIDTH 1280
#define WINDOW_RESOLUTION_HEIGHT 800

#define CHESS_IMG_SCALE 0.11f
#define CHESSBOARD_IMG_SCALE 0.31f

#define DELAY_TIME 100

/* Resource */
namespace Textures
{
	enum class ID {
		Chess_King_Red,
		Chess_Advisors_Red,
		Chess_Minister_Red,
		Chess_Chariots_Red,
		Chess_Knights_Red,
		Chess_Cannons_Red,
		Chess_Soldiers_Red,

		Chess_King_Black,
		Chess_Advisors_Black,
		Chess_Minister_Black,
		Chess_Chariots_Black,
		Chess_Knights_Black,
		Chess_Cannons_Black,
		Chess_Soldiers_Black,

		CheckBoard
	};
}
namespace Fonts {
	enum class ID
	{
		BiauKai
	};
}

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

/* Game Status */
enum class Status
{
	WaitBlackPressed,
	WaitBlackPathPressed,

	WaitRedPressed,
	WaitRedPathPressed,
};
/* Chess Characters */
enum class Characters
{
	King,
	Advisors,
	Minister,
	Chariots,
	Knights,
	Cannons,
	Soldiers,
};
/* Player Team */
enum class Team
{
	Red,
	Black
};

/* Global Status */
namespace States {
	enum class ID
	{
		Title,
		Menu,
		ServerMenu,
		ServerEnterIpMenu,
		MultiplayerMenu,
		MultiplayerGame,
		BlackIsCheckMate,
		RedIsCheckMate,
		BlackIsStalemate,
		RedIsStalemate,
		Game,
		Pause,
		End,
	};
}

/* Global Status community */
class StateContext
{
public:
	StateContext(sf::RenderWindow* _window
				, FontHolder* _fontHolder
				, TextureHolder* _textureHolder)
	{
		fontHolder = _fontHolder;
		window = _window;
		textureHolder = _textureHolder;
	};
	sf::RenderWindow* window;
	FontHolder* fontHolder;
	TextureHolder* textureHolder;
};