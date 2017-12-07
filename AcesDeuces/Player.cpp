#include "Player.hpp"
#include "Util.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>

Player::Player():
	name(""), human(false), showOdds(true), currentHand(nullptr),
	chipsBalance(0) {};

Player::Player(std::string const& name, bool isHuman, bool showOdds):
	name(name), human(isHuman), showOdds(showOdds), currentHand(nullptr),
	chipsBalance(0) {};

int Player::getChipBalance() {
	return chipsBalance;
}

void Player::addChips(int amount) {
	chipsBalance += amount;
}

void Player::removeChips(int amount) {
	chipsBalance = chipsBalance - amount;
}

Hand* Player::getCurrentHand() {
	return currentHand;
}

void Player::setCurrentHand(Hand &hand) {
	currentHand = &hand;
}

void Player::clearHand() {
	currentHand = nullptr;
}

bool Player::isHuman() const {
	return human;
}

bool Player::operator==(const Player& p) const{
	return &p == this;
}

std::ostream& operator<<(std::ostream& os, Player p) {
	return os << "Name: " << p.name << std::endl
		<< "Is Human: " << (p.isHuman() ? "Yes" : "No") << std::endl
		<< "Show Odds: " << (p.showOdds ? "Yes" : "No") << std::endl
		<< "Chips Balance: " << p.getChipBalance() << std::endl;
}

std::string Player::getLeaderBoardName() {
	std::string leaderBoardName = name;
	if (currentHand != nullptr) {
		leaderBoardName+= " (*)";
	}
	alignStringToLeft(leaderBoardName, 27);
	return leaderBoardName;
}

std::string Player::getChipsString() {
	std::string chipsString = std::to_string(this->chipsBalance);
	alignStringToRight(chipsString, 11);
	return chipsString;
}
