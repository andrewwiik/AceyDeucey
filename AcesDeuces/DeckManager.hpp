#ifndef DeckManager_hpp
#define DeckManager_hpp

#include <vector>
#include "Card.hpp"

class DeckManager {
public:
	DeckManager();
	void shuffleCards();
	void newDeck(bool shouldClear);
	void resetDeck();
	int cardsLeftOfRank(Rank r) const;
	int cardsLeftBetweenRanks(Rank r1, Rank r2) const;
	int cardsLeft() const;
	Card drawRandomCard();
	std::vector<Card> getDeck();
	bool displayDeckInfo;
	void checkIfNeedsShuffle();
	
	operator std::string() const;
	operator std::stringstream() const;
private:
	std::vector<Card> deck;
	
};

#endif
