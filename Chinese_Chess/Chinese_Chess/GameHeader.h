#pragma once
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

#define WINDOW_RESOLUTION_WIDTH 1280
#define WINDOW_RESOLUTION_HEIGHT 800

#define CHESS_IMG_SCALE 0.1f
#define CHESSBOARD_IMG_SCALE 0.3f

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

enum class Team
{
	Red,
	Black
};