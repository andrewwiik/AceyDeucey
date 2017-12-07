#ifndef Hand_hpp
#define Hand_hpp

#include "Card.hpp"

enum class BetDirection {
	Low,
	High,
	Unknown
};

class Hand
{
public:
	Hand (Card &c1, Card &c2, BetDirection betDirection = BetDirection::Unknown);
	Card low;
	Card high;
	Card thirdCard;
	
	operator std::string() const;
	operator std::stringstream() const;
	
	BetDirection betDirection;
};

#endif
