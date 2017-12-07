#include "Card.hpp"
#include "Util.hpp"

Card::Card(Rank rank, Suit suit) : rank(rank), suit(suit) {}

std::string Card::getRankString() const {
	switch (rank) {
		case Rank::Ace:
			return "A";
		case Rank::Two:
			return "2";
		case Rank::Three:
			return "3";
		case Rank::Four:
			return "4";
		case Rank::Five:
			return "5";
		case Rank::Six:
			return "6";
		case Rank::Seven:
			return "7";
		case Rank::Eight:
			return "8";
		case Rank::Nine:
			return "9";
		case Rank::Ten:
			return "10";
		case Rank::Jack:
			return "J";
		case Rank::Queen:
			return "Q";
		case Rank::King:
			return "K";
		case Rank::Unknown:
			return "U";
	}
	return "";
}

std::string Card::getSuitString() const {
	switch (suit) {
		case Suit::Hearts:
			return "♥"; //7
		case Suit::Diamonds:
			return "♦";
		case Suit::Clubs:
			return "♣";
		case Suit::Spades:
			return "♠";
		case Suit::Unknown:
			return "?";
	}
	return "";
}

bool Card::isUnknownCard() const {
	return rank == Rank::Unknown && suit == Suit::Unknown;
}

Card::operator std::string() const {
	if (isUnknownCard()) {
		  return "┌───────┐ \n"
				 "│░░░░░░░│ \n"
				 "│░░░░░░░│ \n"
				 "│░░░░░░░│ \n"
				 "│░░░░░░░│ \n"
				 "│░░░░░░░│ \n"
				 "└───────┘ \n";
	} else {
		std::string card =	"┌───────┐ \n"
							"│TP     │ \n"
							"│       │ \n"
							"│   S   │ \n"
							"│       │ \n"
							"│     BT│ \n"
							"└───────┘ \n";
		
		std::string rankString = getRankString();
		replaceStringWithString(
			card,
			"TP",
			(rankString.length() > 1 ? rankString : rankString + " ")
		);
		
		replaceStringWithString(card, "S", getSuitString());
		
		replaceStringWithString(
			card,
			"BT",
			(rankString.length() > 1 ? rankString : " " + rankString)
		);
		return card;
	}
}

Card::operator std::stringstream() const {
	return std::stringstream(static_cast<std::string>(*this));
}


bool Card::operator==(const Card& c1) const {
	return rank == c1.rank && suit == c1.suit;
}

bool Card::operator!=(const Card& c1) const {
	return rank != c1.rank || suit != c1.suit;
}

bool Card::operator<(const Card& c1) const {
	return rank < c1.rank;
}

bool Card::operator>(const Card& c1) const {
	return rank > c1.rank;
}

bool Card::operator<=(const Card& c1) const {
	return rank <= c1.rank;
}

bool Card::operator>=(const Card& c1) const {
	return rank >= c1.rank;
}

std::string fullStringForRank(Rank r) {
	switch (r) {
		case Rank::Ace:
			return "Ace";
		case Rank::Two:
			return "Two";
		case Rank::Three:
			return "Three";
		case Rank::Four:
			return "Four";
		case Rank::Five:
			return "Five";
		case Rank::Six:
			return "Six";
		case Rank::Seven:
			return "Seven";
		case Rank::Eight:
			return "Eight";
		case Rank::Nine:
			return "Nine";
		case Rank::Ten:
			return "Ten";
		case Rank::Jack:
			return "Jack";
		case Rank::Queen:
			return "Queen";
		case Rank::King:
			return "King";
		case Rank::Unknown:
			return "Unkown";
	}
	return "";
}
