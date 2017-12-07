#ifndef GameManager_hpp
#define GameManager_hpp

#include <stdio.h>
#include "Game.hpp"
#include "Player.hpp"

class GameManger {
public:
	Game createGame();
	void getGameOptions();
	bool getNumberOfAIPlayers(int* numOfAIPlayers);
	bool getNumberOfHumanPlayers(int* numOfHumanPlayers, int numOfAI);
	bool getHumanPlayerInformation(std::string& playerName,
											bool* showOdds,
										  int playerNumber);
	
	bool getDefaultAnte(int *defaultAnte);
	bool getStartingChipsForPlayers(int *startingChips); 
	
private:
	Game currentGame;
};

#endif
