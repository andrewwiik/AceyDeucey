#include "Bet.hpp"

Bet::Bet(int betAmount): player(nullptr) {
//	player = player;
	amount = betAmount;
}

void Bet::setPlayer(Player* p) {
	player = p;
}

Player* Bet::getPlayer() {
	return player;
}

int Bet::getBetAmount() {
	return amount;
} 
