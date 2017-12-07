#ifndef GameRenderer_hpp
#define GameRenderer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "PotManager.hpp"
#include "DeckManager.hpp"
#include "OddsManager.hpp"
#include "Player.hpp"
#include "LeaderBoard.hpp"

class Game;

class GameRenderer {
public:
	void setObjects(PotManager* potManager, DeckManager* deckManager,
									OddsManager* oddsManager, 
									std::vector<Player>* players);
	void renderScreen(int sleepFor = 0);
	void setBottomString(const std::string bottomString, int sleepFor = 0);
	void setCurrentPlayer(Player* player);
	void setPlayers(std::vector<Player>* players);
	
private:
	LeaderBoard leaderBoard;
	PotManager* potManager;
	DeckManager* deckManager;
	OddsManager* oddsManager;
	Player* currentPlayer;
	std::string bottomString;
	std::vector<Player>* players;
};

#endif
