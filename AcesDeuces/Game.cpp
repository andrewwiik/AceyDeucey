#include "Game.hpp"
#include <time.h>
#include <sstream>
#include "BetValidityStatus.hpp"
#include "LeaderBoard.hpp"
#include "Util.hpp"

/* because two remove methods exist, one for files and one for containers,
 If I want the container one I must import the algorithm header */

#include <algorithm>

Game::Game() {
	defaultAnte = 1;
	startingChips = 0;
	currentPlayer = nullptr;
}

void Game::addPlayer(Player player) {
	player.addChips(startingChips);
	players.push_back(player);
	if (player.isHuman()) {
		std::cout << "\"" << player.name;
		std::cout << "\" was successfully added to the game.";
		std::cout << std::endl << std::endl;
	}
}

void Game::removePlayer(Player* player) {
	players.erase(
		std::remove(players.begin(), players.end(), *player), players.end()
	);
	
	lastPlayerLost = true;
}

void Game::setDefaultAnte(int ante) {
	potManager.setDefaultAnte(ante);
}

void Game::gatherAnte() {
	for (auto i = players.begin(); i != players.end(); ++i) {
		getAnteFromPlayer(&*i);
	}
}

void Game::getAnteFromPlayer(Player* player) {
	if (!potManager.collectAnteForPlayer(*player)) {
		std::cout << "\"" << player->name;
		std::cout << "\" was removed from the game because ";
		std::cout << "they had insuffecient chips to ante." << std::endl;
		removePlayer(player);
	}
}

void Game::startGame() {
	potManager.setDelegate(this);
	gatherAnte();
	renderer.setObjects(&potManager, &deckManager, &oddsManager, &players);
	
	while(players.size() > 1) {
		
		/* I'm not using an iterator here because I
		   might be removing a player from vector 
		   while I'm looping and using an iterator
		   when doing that causes me to walk off 
		   the end.
		 */
		
		for (int x = 0; x < players.size(); x++) {
			if (players.size() > 1) {
				processTurnForPlayer(players[x]);
				if (lastPlayerLost) {
					x--;
				}
			}
			
			lastPlayerLost = false;
		}
	}
	
	if (players.size() == 1) {
		std::cout << std::endl << "Congratulations ";
		std::cout << players[0].name << ", You have Won!!!";
		std::cout << std::endl << std::endl;
	}
}

bool Game::getWantsToBetForTurn(bool* wantsToBet) {
	if (currentPlayer->isHuman()) {
		std::string wantsToBetInput = "";
		renderer.setBottomString("Would you like to Bet? [Y/N]: ");
		std::cin >> wantsToBetInput;
		if (wantsToBetInput.empty() == false) {
			switch (tolower(wantsToBetInput[0]))
			{
				case 'y': {
					*wantsToBet = true;
					return true;
				}
				case 'n': {
					*wantsToBet = false;
					return true;
				}
			}
		}
		renderer.setBottomString("Please Enter a Valid Option.", 1250);
		return false;
	} else {
		renderer.setBottomString("Would you like to Bet? [Y/N]: ", 1250);
		*wantsToBet = aiManager.playerShouldBet(currentPlayer,
												 &deckManager,
												 &oddsManager);
		std::string autoBetAnswer ="Would you like to Bet? [Y/N]: ";
		autoBetAnswer += (wantsToBet ? "Y" : "N");
		renderer.setBottomString(autoBetAnswer, 1250);
		return true;
	}
	return false;
}

bool Game::getBetAmountForTurn(int* betAmount) {
	if (currentPlayer->isHuman()) {
		std::string betAmountInput = "";
		BetValidityStatus betStatus = BetValidityStatus::Unknown;
		renderer.setBottomString("How much would you like to bet: ");
		std::cin >> betAmountInput;
		std::stringstream validityStream(betAmountInput);
		if (validityStream >> *betAmount) {
			if (*betAmount > 0) {
				betStatus = potManager.isValidBet(*currentPlayer, *betAmount);
				if (betStatus == BetValidityStatus::Valid) {
					return true;
				}
			}
		}
			
		if (betStatus == BetValidityStatus::PlayerHasInsufficientChips) {
			renderer.setBottomString("You do not have enough chips "
									 "to bet that amount.", 1250);
		} else if (betStatus == BetValidityStatus::PotHasInsufficientChips) {
			renderer.setBottomString("You cannot bet more than "
									 "what the pot holds.", 1250);
		} else {
			renderer.setBottomString("Please enter a valid bet amount.", 1250);
		}
		*betAmount = 0;
		return false;
	} else {
		*betAmount = aiManager.playerShouldBetAmount(currentPlayer,
													  &deckManager,
											          &oddsManager,
											          &potManager);

		renderer.setBottomString("How much would you like to bet: ", 1250);
		std::string outputString = "How much would you like to bet: ";
		outputString += std::to_string(*betAmount);
		renderer.setBottomString(outputString, 1250);
		return true;
	}
}

bool Game::getBetDirectionForTurn(BetDirection* betDirection) {
	if (currentPlayer->isHuman()) {
		std::string wantsToBetInput = "";
		renderer.setBottomString("Would you like to bet High or Low? [H/L]: ");
		std::cin >> wantsToBetInput;
		if (wantsToBetInput.empty() == false) {
			switch (tolower(wantsToBetInput[0]))
			{
				case 'h': {
					*betDirection = BetDirection::High;
					return true;
				}
				case 'l': {
					*betDirection = BetDirection::Low;
					return true;
				}
			}
		}
		renderer.setBottomString("Please Enter a Valid Option.", 1250);
		return false;
	} else {
		renderer.setBottomString("Would you like to bet "
								 "High or Low? [H/L]: ", 1250);
		*betDirection = aiManager.playerShouldBetInDirection(currentPlayer,
															  &deckManager,
															  &oddsManager);
		std::string autoAnswer = "Would you like to "
											 "bet High or Low? [H/L]: ";
		autoAnswer += (*betDirection == BetDirection::High ? "H" : "L");
		renderer.setBottomString(autoAnswer, 1250);
		return true;
	}
	return false;
}

void Game::processPlayerWon() {
	potManager.playerWonBet();
	renderer.setBottomString("Congratulations, you won, you get double"
							 " your bet back!!!", 1750);
}

void Game::processPlayerLost() {
	potManager.playerLostBet();
	if (currentPlayer->getChipBalance() <= 0) {
		currentPlayer->clearHand();
		removePlayer(currentPlayer);
		renderer.setCurrentPlayer(nullptr);
		renderer.setBottomString("Aw you lost and are out chips, goodbye :)",
								 1750);
		currentPlayer = nullptr;
	} else {
		renderer.setBottomString("Congratulations, you are a loser,"
								 " you probably should quit :)", 1750);
	}
}

void Game::processPlayerTied() {
	potManager.playerTiedBet();
	renderer.setBottomString("Hey you tied, you don't gain anything but also "
							 "lose nothing", 1750);
}

void Game::checkIfPlayerWonTurn() {
	Hand* currentHand = currentPlayer->getCurrentHand();
	Card low = currentHand->low;
	Card high = currentHand->high;
	Card third = currentHand->thirdCard;
	BetDirection direction = currentHand->betDirection;
	if (low.rank != high.rank) {
		if (third > low && third < high) {
			processPlayerWon();
		} else {
			processPlayerLost();
		}
	} else {
		if (direction == BetDirection::High) {
			if (third > high) {
				processPlayerWon();
			} else {
				processPlayerLost();
			}
		} else {
			if (third < low) {
				processPlayerWon();
			} else {
				processPlayerLost();
			}
		}
	}
}

void Game::processTurnForPlayer(Player& player) {
	currentPlayer = &player;
	renderer.setPlayers(&players);
	deckManager.displayDeckInfo = currentPlayer->showOdds;
	
	Card c1 = drawRandomCard();
	Card c2 = drawRandomCard();
	Hand hand = Hand(c1, c2);
	currentPlayer->setCurrentHand(hand);
	oddsManager.processOddsForPlayer(currentPlayer,&deckManager);
	renderer.setCurrentPlayer(currentPlayer);
	
	bool wantsToBet = false;
	
	while (!getWantsToBetForTurn(&wantsToBet));
	
	if (wantsToBet) {
		int betAmount = 0;
		
		if (c1.rank == c2.rank) {
			std::string infoString = "You have drawn two of the same card, "
									 "you must choose to either bet high "
									 "or low.";

			renderer.setBottomString(infoString, 1250);
			BetDirection betDirection = BetDirection::Unknown;
			while(!getBetDirectionForTurn(&betDirection));
			currentPlayer->getCurrentHand()->betDirection = betDirection;
			oddsManager.processOddsForPlayer(currentPlayer,&deckManager);
		}
		
		while(!getBetAmountForTurn(&betAmount));
		Bet bet = Bet(betAmount);
		bet.setPlayer(currentPlayer);
		potManager.setCurrentBet(&bet);
		currentPlayer->getCurrentHand()->thirdCard = drawRandomCard();
		checkIfPlayerWonTurn();
	}
	if (currentPlayer != nullptr) {
		currentPlayer->clearHand();
	}
	deckManager.checkIfNeedsShuffle();
}

void Game::printPlayers() {
	for (auto i = players.begin(); i != players.end(); ++i) {
		
		std::cout << *i << std::endl;
	}
}

void Game::setStartingChips(int amount) {
	startingChips = amount;
}

Card Game::drawRandomCard() {
	return deckManager.drawRandomCard();
}

void Game::potWasEmptied() {
	gatherAnte();
}
