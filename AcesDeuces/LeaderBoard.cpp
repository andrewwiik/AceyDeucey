#include "LeaderBoard.hpp"
#include "Util.hpp"

void LeaderBoard::setPlayers(std::vector<Player>* playersVec) {
	players = playersVec;
}


LeaderBoard::operator std::string() {
	
	/*
	 ┌LeaderBoard──────────────────┬─────────────┐
	 │ Player Name                 │ # of Chips  │
	 ├─────────────────────────────┼─────────────┤
	 │ Andrew Wiik                 │         500 │
	 │ Bob Dylan                   │        1000 │
	 │ Tom Scott                   │         700 │
	 │ AI Player #1                │        1000 │
	 │ AI Player #2                │        1000 │
	 │ AI Player #3                │        1000 │
	 │                             │             │
	 └─────────────────────────────┴─────────────┘
	*/
	 
	std::string board =
	"┌LeaderBoard──────────────────┬─────────────┐\n"
	"│ Player Name                 │ # of Chips  │\n"
	"├─────────────────────────────┼─────────────┤\n";
	
	
	//std::string playerString = "│ NAME │ CHIP │\n";
	
	for (auto i = players->begin(); i != players->end(); ++i) {
		std::string playerString = "│ 66 │ 77 │\n";
		Player player = *i;
		replaceStringWithString(playerString, "66", player.getLeaderBoardName());
		replaceStringWithString(playerString, "77", player.getChipsString());
		
		board+= playerString;
	}
	
	for (int x = int(players->size()) - 1; x < 7; x++) {
		board += "│                             │             │\n";
	}
	
	board += "└─────────────────────────────┴─────────────┘\n";
	return board;
}

LeaderBoard::operator std::stringstream() {
	return std::stringstream(static_cast<std::string>(*this));
}
