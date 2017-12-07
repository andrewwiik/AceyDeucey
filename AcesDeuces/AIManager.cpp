#include "AIManager.hpp"

bool AIManager::playerShouldBet(Player* player, 
						   DeckManager* deckManager,
						   OddsManager* oddsManager) {
	return rand() % 2 == 0;
}

int AIManager::playerShouldBetAmount(Player* player,
								DeckManager* deckManager,
								OddsManager* oddsManager,
								 PotManager* potManager) {

	int upperBound = potManager->getPotAmount();
	if (upperBound > player->getChipBalance()) {
		upperBound = player->getChipBalance();
	}
	return 	std::rand()%(abs((upperBound-1))+1)+1;
}

BetDirection AIManager::playerShouldBetInDirection(Player* player,
											  DeckManager* deckManager,
											  OddsManager* oddsManger) {
	if (rand() % 2 == 0) {
		return BetDirection::Low;
	} else {
		return BetDirection::High;
	}
}
