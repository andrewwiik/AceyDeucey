#ifndef Card_hpp
#define Card_hpp

#include <iostream>
#include <sstream>

enum class Rank {
  Ace,
  Two,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Unknown
};

//suits of cards in a deck
enum class Suit {
  Hearts,
  Diamonds,
  Clubs,
  Spades,
  Unknown
};

class Card {
public:
  Card (Rank rank = Rank::Unknown, Suit suit = Suit::Unknown);
  Rank rank;
  Suit suit;
  std::string getRankString() const;
  std::string getSuitString() const;
  
  bool isUnknownCard() const;
  
  // Overloaded Operators
  bool operator==(const Card& c1) const;
  bool operator!=(const Card& c1) const;
  bool operator<(const Card& c1) const;
  bool operator>(const Card& c1) const;
  bool operator<=(const Card& c1) const;
  bool operator>=(const Card& c1) const;
  
  operator std::string() const;
  operator std::stringstream() const;
};

std::string fullStringForRank(Rank r);
#endif
