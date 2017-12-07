#include "OddsManager.hpp"
#include "Util.hpp"

OddsManager::OddsManager() : currentPlayer(nullptr), currentDeck(nullptr) {}

void OddsManager::processOddsForPlayer(Player* player, DeckManager* deck) {
	currentDeck = deck;
	currentPlayer = player;
	chanceOfWinning = 0.0;
	
	if (player->showOdds) {
		Card low = player->getCurrentHand()->low;
		Card high = player->getCurrentHand()->high;
		BetDirection betDirection = player->getCurrentHand()->betDirection;
		int cardsInDeck = deck->cardsLeft();
		
		if (low.rank == high.rank) {
			if (betDirection == BetDirection::Low) {
				int possLC = deck->cardsLeftBetweenRanks(Rank::Ace, low.rank);
				if (low.rank != Rank::Ace) {
					possLC += deck->cardsLeftOfRank(Rank::Ace);
				}
				
				double lowChance = double(possLC)/double(cardsInDeck);
				lowChance = lowChance*100;
				oddsString = doubleToStringWithPrecision(lowChance, 1);
				oddsString += "%";
			} else if (betDirection == BetDirection::High) {
				
				int possHC = deck->cardsLeftBetweenRanks(high.rank, Rank::King);
				if (high.rank != Rank::King) {
					possHC += deck->cardsLeftOfRank(Rank::King);
				}
				double highChance =  double(possHC)/double(cardsInDeck);
				highChance = highChance*100;
				oddsString = doubleToStringWithPrecision(highChance, 1);
				oddsString += "%";
			} else {
				
				int possLC = deck->cardsLeftBetweenRanks(Rank::Ace, low.rank);
				if (low.rank != Rank::Ace) {
					possLC += deck->cardsLeftOfRank(Rank::Ace);
				}
				
				double lowChance = double(possLC)/double(cardsInDeck);
				lowChance = lowChance*100;
				
				oddsString = "Low: ";
				oddsString += doubleToStringWithPrecision(lowChance, 1);
				oddsString += "%  High: ";
				
				int possHC = deck->cardsLeftBetweenRanks(high.rank, Rank::King);
				if (high.rank != Rank::King) {
					possHC += deck->cardsLeftOfRank(Rank::King);
				}
				double highChance =  double(possHC)/double(cardsInDeck);
				highChance = highChance*100;
				oddsString += doubleToStringWithPrecision(highChance, 1);
				oddsString += "%";
			}
		} else {
			int possibleWinCards = deck->cardsLeftBetweenRanks(low.rank,
															  high.rank);
			
			double chance = double(possibleWinCards)/double(cardsInDeck);
			chance *= 100;
			oddsString = doubleToStringWithPrecision(chance, 1);
			oddsString += "%";
		}
	} else {
		chanceOfWinning = 0.0;
	}
}

bool OddsManager::shouldHideOdds() const {
	if (currentPlayer != nullptr) {
		return !currentPlayer->showOdds;
	} else return true;
}

OddsManager::operator std::string() const {
	std::string oddsView =
		"┌Odds───────────────────────────────────────┐\n"
		"│   Your chances of winning this hand are:  │\n"
		"│ ";
	
	std::string chanceStr = "";
	if (!shouldHideOdds()) {
		chanceStr = oddsString;
	} else {
		chanceStr = "Unavailable";
	}
	
	alignStringToCenter(chanceStr, 41);
	
	oddsView += chanceStr;
	
	oddsView += " │\n"
	"└───────────────────────────────────────────┘\n";
	
	return oddsView;
}

OddsManager::operator std::stringstream() const {
	return std::stringstream(static_cast<std::string>(*this));
}
