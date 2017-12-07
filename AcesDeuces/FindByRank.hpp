#ifndef FindByRank_hpp
#define FindByRank_hpp

#include "Card.hpp"

class FindByRank {
public:
	FindByRank(Rank rank) : rank(rank) {}
	Rank rank;
	
	bool operator()(const Card& card) const
	{ return card.rank == rank; }
};

#endif
