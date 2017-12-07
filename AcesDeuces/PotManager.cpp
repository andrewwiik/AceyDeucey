#include "PotManager.hpp"
#include "Util.hpp"

PotManager::PotManager() : currentBet(nullptr), currentPot(0), defaultAnte(0),
	delegate(nullptr) {}

int PotManager::getPotAmount() {
	return currentPot;
}

void PotManager::playerLostBet() {
	if (currentBet != nullptr) {
		int betAmount = currentBet->getBetAmount();
		currentBet->getPlayer()->removeChips(betAmount);
		addToPot(betAmount);
		currentBet = nullptr;
	}
}

void PotManager::playerWonBet() {
	if (currentBet != nullptr) {
		int betAmount = currentBet->getBetAmount();
		currentBet->getPlayer()->addChips(betAmount);
		subtractFromPot(betAmount);
		currentBet = nullptr;
	}
}

void PotManager::playerTiedBet() {
	if (currentBet != nullptr) {
		currentBet = nullptr;
	}
}

void PotManager::setCurrentBet(Bet* bet){
	currentBet = bet;
}

bool PotManager::collectAnteForPlayer(Player& player) {
	if (playerCanAnte(player)) {
		player.removeChips(defaultAnte);
		addToPot(defaultAnte);
		return true;
	}
	return false;
}

BetValidityStatus PotManager::isValidBet(Player &player, int amount) {
	if (amount > currentPot)
		return BetValidityStatus::PotHasInsufficientChips;
	if (player.getChipBalance() < amount)
		return BetValidityStatus::PlayerHasInsufficientChips;
	else return BetValidityStatus::Valid;
}

void PotManager::setDefaultAnte(int ante) {
	defaultAnte = ante;
}

bool PotManager::playerCanAnte(Player& player) {
	if (player.getChipBalance() <= defaultAnte) return false;
	return true;
}

void PotManager::subtractFromPot(int amount) {
	if (currentPot >= amount) {
		currentPot-= amount;
		if (currentPot == 0) {
			if (delegate != nullptr) {
				delegate->potWasEmptied();
			}
		}
	}
}

void PotManager::addToPot(int amount) {
	if (amount >= 0) {
		currentPot+= amount;
	}
}

void PotManager::setDelegate(PotManagerDelegate* del) {
	delegate = del;
}

/*  ┌Pot──────────────────────────────┐
	│ Cureent Pot:         4000 chips │
	│ Default Ante:           5 chips │
	└─────────────────────────────────┘
 */

PotManager::operator std::string() const {
	
	std::string box =
	"┌Pot──────────────────────────────┐\n"
	"│ Current Pot: CP chips │\n"
	"│ Default Ante: DA chips │\n"
	"└─────────────────────────────────┘\n";
	
	std::string potString = std::to_string(currentPot);
	alignStringToRight(potString, 12);
	
	std::string anteString = std::to_string(defaultAnte);
	alignStringToRight(anteString, 11);
	
	replaceStringWithString(box,"CP", potString);
	replaceStringWithString(box,"DA", anteString);
	
	return box;
}

PotManager::operator std::stringstream() const {
	return std::stringstream(static_cast<std::string>(*this));
}
