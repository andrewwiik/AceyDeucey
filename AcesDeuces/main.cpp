#include <iostream>
#include "GameManager.hpp"
#include "Hand.hpp"
#include "IntroScreenRenderer.hpp"
#include <sstream>


int main(int argc, const char * argv[]) {
	
	IntroScreenRenderer introRender = IntroScreenRenderer();
	introRender.renderScreen();
	
	std::cout << "Press enter to continue...";
	std::cin.ignore();
	
	GameManger gameManager = GameManger();
	Game game = gameManager.createGame();
	game.startGame();
	
	return 0;
}
