#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include "Card.hpp"
#include "Hand.hpp"
#include <iostream>

class Player
{
public:
	
	Player(); // Default Constructor

	// Constructor
	Player(std::string const& name, bool isHuman, bool showOdds);
	
	// Public Member Variables
	std::string name;
	bool showOdds;
	
	// Handle Player Balance
	int getChipBalance();
	void addChips(int amount);
	void removeChips(int amount);
	
	// Handle Player Hand
	Hand* getCurrentHand();
	void setCurrentHand(Hand &hand);
	void clearHand();
	
	// Is Human
	bool isHuman() const;
	bool operator==(const Player& p) const;
	
	std::string getChipsString();
	std::string getLeaderBoardName();
	
private:
	std::string leaderBoardName;
	std::string chipsString;
	void recomputeChipString();
	void recomputeLeaderBoardName();
	Hand* currentHand;
	int chipsBalance;
	bool human;
};

std::ostream& operator<<(std::ostream& os, Player p);

#endif
