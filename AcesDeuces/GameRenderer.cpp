#include "GameRenderer.hpp"
#include "Util.hpp"

void GameRenderer::setObjects(PotManager* potManager,
							DeckManager* deckManager,
							OddsManager* oddsManager,
						std::vector<Player>* players) {

	this->potManager = potManager;
	this->deckManager = deckManager;
	this->oddsManager = oddsManager;
	this->players = players;
	leaderBoard.setPlayers(players);
}

void GameRenderer::setPlayers(std::vector<Player>* players){
	leaderBoard.setPlayers(players);
	
}

void GameRenderer::setCurrentPlayer(Player *player) {
	currentPlayer = player;
}

void GameRenderer::renderScreen(int sleepFor) {
	std::vector<std::string> output(24);
	
	std::stringstream board = leaderBoard;
	std::stringstream deck = *deckManager;
	std::stringstream pot = *potManager;
	std::stringstream odds = *oddsManager;
	
	int x = 0;
	std::string line = "";
	
	while (std::getline(pot, line)) {
		output[x] += line;
		x++;
		line = "";
	}
	
	while (std::getline(deck, line)) {
		output[x] += line;
		x++;
		line = "";
	}
	
	x= 0;
	
	while (std::getline(board, line)) {
		output[x] += line;
		x++;
		line = "";
	}
	
	while (std::getline(odds, line)) {
		output[x] += line;
		x++;
		line = "";
	}
	
	if (currentPlayer != nullptr) {
		std::stringstream hand = *currentPlayer->getCurrentHand();
		while (std::getline(hand, line)) {
			output[x] += line;
			x++;
			line = "";
		}
	}
	
	for (int b = 0; b < 7; b++) {
		std::cout << std::endl;
	}
	
	for (auto s = output.begin(); s != output.end(); ++s) {
		std::cout << *s << std::endl;
	}
	
	std::cout << this->bottomString;
	std::cout.flush();
	if (sleepFor > 0) {
		std::cout.flush();
		msleep(sleepFor);
		
	}
}

void GameRenderer::setBottomString(const std::string bottomStr, int sleepFor) {
	bottomString = bottomStr;
	renderScreen(sleepFor);
}
