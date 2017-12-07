#ifndef Bet_hpp
#define Bet_hpp

#include <stdio.h>
#include "Player.hpp"

class Bet {
public:
	Bet(int betAmount);
	int getBetAmount();
	void setPlayer(Player* p);
	Player* getPlayer();
private:
	int amount;
	Player* player;
};

#endif
