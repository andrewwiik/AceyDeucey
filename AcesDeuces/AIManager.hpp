#ifndef AIManager_hpp
#define AIManager_hpp

#include <stdio.h>
#include "DeckManager.hpp"
#include "Player.hpp"
#include "OddsManager.hpp"
#include "PotManager.hpp"
#include "Hand.hpp"

class AIManager {
public:
	bool playerShouldBet(Player* player,
					DeckManager* deckManager,
					OddsManager* oddsManager);
	
	int playerShouldBetAmount(Player* player,
						 DeckManager* deckManager,
					     OddsManager* oddsManager, 
					      PotManager* potManager);
	
	BetDirection playerShouldBetInDirection(Player* player,
									   DeckManager* deckManager,
									   OddsManager* oddsManger);
};

#endif
