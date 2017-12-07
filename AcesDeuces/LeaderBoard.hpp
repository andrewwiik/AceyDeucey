#ifndef LeaderBoard_hpp
#define LeaderBoard_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Player.hpp"

class LeaderBoard {
public:
	void setPlayers(std::vector<Player>* players);
	operator std::string() ;
	operator std::stringstream();
	
private:
	std::vector<Player>* players;
};

#endif
