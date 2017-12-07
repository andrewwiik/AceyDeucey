#include "DeckManager.hpp"
#include "FindByRank.hpp"
#include "FindBetweenRanks.hpp"
#include <time.h>
#include "Util.hpp"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>


DeckManager::DeckManager() {
	newDeck(false);
	displayDeckInfo = false;
}

void DeckManager::newDeck(bool shouldClear) {
	if (shouldClear) deck.clear();
	std::srand (unsigned(time(NULL)+1));
	deck.reserve(52);
	
	for (int r = int(Rank::Ace); r <= int(Rank::King); ++r){
		for (int s = int(Suit::Hearts); s <= int(Suit::Spades); ++s){
			Card c(static_cast<Rank>(r), static_cast<Suit>(s));
			deck.push_back(c);
		}
	}
	
	shuffleCards();
}

void DeckManager::shuffleCards() {
		std::srand (unsigned(time(NULL)+1));
	std::mt19937 g(std::rand());
	std::shuffle(deck.begin(), deck.end(), g);
}

void DeckManager::resetDeck() {
	newDeck(true);
}

int DeckManager::cardsLeftOfRank(Rank r) const {
	return static_cast<int>(std::count_if(deck.begin(),
										  deck.end(),
									      FindByRank(r)));
}

int DeckManager::cardsLeftBetweenRanks(Rank r1, Rank r2) const {
	return static_cast<int>(std::count_if(deck.begin(),
										  deck.end(),
										  FindBetweenRanks(r1, r2)));
}

int DeckManager::cardsLeft() const {
	return static_cast<int>(deck.size());
}

Card DeckManager::drawRandomCard() {
	auto card = deck.back();
	deck.pop_back();
	return card;
}

std::vector<Card> DeckManager::getDeck(){
	return deck;
}

void DeckManager::checkIfNeedsShuffle() {
	if (cardsLeft() < 3) {
		resetDeck();
	}
}


/*
 ┌Cards in Deck───┬────────┬───────┐
 │ Rank           │ # Left │   %   │
 ├────────────────┼────────┼───────┤
 │ Ace            │        │       │
 │ Two            │        │       │
 │ Three          │        │       │
 │ Four           │        │       │
 │ Five           │        │       │
 │ Six            │        │       │
 │ Seven          │        │       │
 │ Eight          │        │       │
 │ Nine           │        │       │
 │ Ten            │        │       │
 │ Jack           │        │       │
 │ Queen          │        │       │
 │ King           │        │       │
 ├────────────────┴────────┴───────┤
 │ Remaining cards in deck:     32 │
 └─────────────────────────────────┘
 */


DeckManager::operator std::string() const {
	
	std::string deckDisplay =
		"┌Cards in Deck──┬────────┬────────┐\n"
		"│ Rank          │ # Left │    %   │\n"
	  "├───────────────┼────────┼────────┤\n";
	
	int cardsInDeck = int(deck.size());
	
	for (int r = int(Rank::Ace); r <= int(Rank::King); ++r){
		int numLeft = cardsLeftOfRank(Rank(r));
		std::string rStat = "│ R │      ";
		rStat += (displayDeckInfo ? std::to_string(numLeft) : "X") + " │ P │\n";
		
		std::string rank = fullStringForRank(Rank(r));
		alignStringToLeft(rank, 13);
		
		std::string pLeft = "";
		if (displayDeckInfo) {
			double prc = double(numLeft)/double(cardsInDeck);
			prc *= 100;
			
			pLeft += doubleToStringWithPrecision(prc, 1);
			pLeft += "%";
		} else {
			pLeft += "XXX";
		}
		alignStringToRight(pLeft, 6);
		
		replaceStringWithString(rStat, "R", rank);
		replaceStringWithString(rStat, "P", pLeft);
		
		deckDisplay += rStat;
	}
	
	deckDisplay += "├───────────────┴────────┴────────┤\n";
	std::string cLeftDispString = "│ Remaining cards in deck: L │\n";
	std::string cLeftString = std::to_string(cardsInDeck);
	alignStringToRight(cLeftString, 6);
	
	replaceStringWithString(cLeftDispString, "L", cLeftString);
	deckDisplay += cLeftDispString;
	deckDisplay += "└─────────────────────────────────┘\n";
	
	return deckDisplay;
}

DeckManager::operator std::stringstream() const {
	return std::stringstream(static_cast<std::string>(*this));
}


