#include <iostream>
#include <string>
#include <sstream>

#include "GameManager.hpp"

Game GameManger::createGame() {
	currentGame = Game();
	getGameOptions();
	
	std::cout << std::endl;
	
	currentGame.printPlayers();
	
	return currentGame;
}

void GameManger::getGameOptions() {
	int numOfAIPlayers = 0;
	int numOfHumanPlayers = 0;
	int defaultAnte = 0;
	int startingChips = 0;
	
	while(!getStartingChipsForPlayers(&startingChips));
	currentGame.setStartingChips(startingChips);
	
	while(!getDefaultAnte(&defaultAnte));
	currentGame.setDefaultAnte(defaultAnte);
	
	while (!getNumberOfAIPlayers(&numOfAIPlayers));
	if (numOfAIPlayers < 8) {
		while (!getNumberOfHumanPlayers(&numOfHumanPlayers, numOfAIPlayers));
	}
	
	for (int gotPlayers = 0; gotPlayers < numOfHumanPlayers; gotPlayers++) {
		std::string playerName = "";
		bool showOdds = false;
		bool gotPlayer = false;
		while(gotPlayer == false) {
			gotPlayer = getHumanPlayerInformation(playerName,
												   &showOdds,
												gotPlayers+1);
		};
		
		currentGame.addPlayer(Player(playerName, true, showOdds));
	}
	
	for (int genAICount = 0; genAICount < numOfAIPlayers; genAICount++) {
		
		std::ostringstream nameStream;
		nameStream << "AI Player " << genAICount + 1;
		currentGame.addPlayer(Player(nameStream.str(), false, true));
	}
}

bool GameManger::getDefaultAnte(int *defaultAnte) {
	std::string input = "";
	int numberGotten = -1;
	
	std::cout << "Please enter the ante per player for the game: ";
	getline(std::cin, input);
	
	std::stringstream validityStream(input);
	if (validityStream >> numberGotten) {
		if (numberGotten > 0) {
			*defaultAnte = numberGotten;
			return true;
		}
	}
	
	std::cout << "Please Enter a valid ante" << std::endl;
	return false;
}

bool GameManger::getStartingChipsForPlayers(int *startingChips) {
	std::string input = "";
	int numberGotten = -1;
	
	std::cout << "Please enter how many chips each player starts with: ";
	getline(std::cin, input);
	
	std::stringstream validityStream(input);
	if (validityStream >> numberGotten) {
		if (numberGotten > 0) {
			*startingChips = numberGotten;
			return true;
		}
	}
	
	std::cout << "Please Enter a valid number of chips" << std::endl;
	return false;
}

bool GameManger::getHumanPlayerInformation(std::string& playerName,
											        bool* showOdds,
												  int playerNumber) {
	std::string gotName = "";
	std::string gotOdds = "";
	std::cout << "Enter Name for Human Player #" << playerNumber << ": ";
	std::getline(std::cin, gotName);
	
	if (gotName.empty()) {
		std::cout << std::endl << "Please Enter a Valid Name for the Player.";
		std::cout << std::endl;
		std::cin.ignore();
		return false;
	}
	
	playerName = gotName;
	
	while(gotOdds.empty()) {
		
		std::cout << "Show odds of winning for this player? [Y/N]: ";
		std::cin >> gotOdds;
		if (gotOdds.empty() == false) {
			switch (tolower(gotOdds[0]))
			{
				case 'y': {
					*showOdds = true;
					std::cin.ignore();
					return true;
				}
				case 'n': {
					*showOdds = false;
					std::cin.ignore();
					return true;
				}
			}
			
			gotOdds = "";
			std::cout << "Please Enter a Valid Option." << std::endl;
		}
	}
	
	return false;
}

bool GameManger::getNumberOfAIPlayers(int* numOfAIPlayers) {
	std::string input = "";
	int numberGotten = -1;
	
	std::cout << "# of AI players "
							 "(max of 8 AI + Human Players combined): ";
	getline(std::cin, input);
	
	std::stringstream validityStream(input);
	if (validityStream >> numberGotten) {
		if (numberGotten >= 0 && numberGotten <= 8) {
			*numOfAIPlayers = numberGotten;
			return true;
		}
	}
	
	std::cout << "Please Enter a Valid Number of AI Players" << std::endl;
	return false;
}

bool GameManger::getNumberOfHumanPlayers(int* numOfHumanPlayers, int numOfAI) {
	std::string input = "";
	int numberGotten = -1;
	std::string inputStr = "# of Human Players (max ";
	inputStr += std::to_string(8 - numOfAI);
	inputStr += "): ";
	std::cout << inputStr;
	getline(std::cin, input);
	
	std::stringstream validityStream(input);
	if (validityStream >> numberGotten) {
		if (numberGotten == 0 && numOfAI > 1) {
			*numOfHumanPlayers = numberGotten;
			return true;
		} else if ((numberGotten > 0 && numOfAI > 0) || numberGotten > 1) {
			*numOfHumanPlayers = numberGotten;
			return true;
		} else {
			std::cout << "The Game must contain at least two total players";
			std::cout << std::endl;
			return false;
		}
	}
	
	std::cout << "Please Enter a Valid Number of Human Players" << std::endl;
	return false;
}
