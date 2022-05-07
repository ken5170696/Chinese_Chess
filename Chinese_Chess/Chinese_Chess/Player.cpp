#include "Player.h"

Player::Player()
{
	Factory chessFac;
	chessFac.getChess(Characters::King);
	for (int charIdx = int(Characters::Advisors); charIdx <= int(Characters::Cannons); charIdx++) {
		for (int num = 0; num < 2; num++) {
			chessFac.getChess(Characters(charIdx));
		}
	}
	for (int num = 0; num < 5; num++) {
		chessFac.getChess(Characters::Soldiers);
	}
}
