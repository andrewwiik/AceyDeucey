#ifndef PotManager_hpp
#define PotManager_hpp

#include <stdio.h>
#include "Bet.hpp"
#include "BetValidityStatus.hpp"
#include "PotManagerDelegate.hpp"

class PotManager {
public:
	PotManager();
	int getPotAmount();
	void addToPot(int amount);
	void subtractFromPot(int amount);
	
	// Ante Handeling
	bool collectAnteForPlayer(Player& player);
	bool playerCanAnte(Player& player);
	void setDefaultAnte(int ante);

	// Bet Handeling
	BetValidityStatus isValidBet(Player &player, int amount);
	void setCurrentBet(Bet* bet);
	void playerLostBet();
	void playerWonBet();
	void playerTiedBet();
	
	// Setting Delegate
	void setDelegate(PotManagerDelegate* delegate);
	
	operator std::string() const;
	operator std::stringstream() const;
private:
	int currentPot;
	int defaultAnte;
	Bet* currentBet;
	PotManagerDelegate* delegate;
};

#endif
