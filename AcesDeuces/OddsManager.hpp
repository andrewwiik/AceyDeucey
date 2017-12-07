#ifndef OddsManager_hpp
#define OddsManager_hpp

#include <stdio.h>
#include "Player.hpp"
#include <iostream>
#include <sstream>
#include "DeckManager.hpp"

class OddsManager {
public:
	OddsManager();
	bool shouldHideOdds() const;
	void processOddsForPlayer(Player* player, DeckManager* deck);
	
	operator std::string() const;
	operator std::stringstream() const;
private:
	double chanceOfWinning;
	std::string oddsString;
	Player* currentPlayer;
	DeckManager* currentDeck;
};

#endif
