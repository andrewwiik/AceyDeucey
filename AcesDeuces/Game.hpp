#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <vector>
#include "Player.hpp"
#include "DeckManager.hpp"
#include "PotManager.hpp"
#include "PotManagerDelegate.hpp"
#include "OddsManager.hpp"
#include "GameRenderer.hpp"
#include "AIManager.hpp"

class GameRenderer;

class Game : public PotManagerDelegate {
public:
	Game();
	void startGame();
	void addPlayer(Player player);
	void removePlayer(Player* player);
	void gatherAnte();
	void getAnteFromPlayer(Player* player);
	void setDefaultAnte(int ante);
	void processTurnForPlayer(Player& player);
	void printPlayers();
	void setStartingChips(int amount);
	Card drawRandomCard();
	void potWasEmptied();
	void checkIfPlayerWonTurn();
	void processPlayerWon();
	void processPlayerLost();
	void processPlayerTied();
	
	// handle player turns
	bool getWantsToBetForTurn(bool* wantsToBet);
	bool getBetAmountForTurn(int* betAmount);
	bool getBetDirectionForTurn(BetDirection* betDirection);
	
private:
	GameRenderer renderer;
	int defaultAnte;
	int startingChips;
	DeckManager deckManager;
	PotManager potManager;
	OddsManager oddsManager;
	AIManager aiManager;
	std::vector<Player> players;
	Player *currentPlayer;
	bool lastPlayerLost;
	
};

#endif
