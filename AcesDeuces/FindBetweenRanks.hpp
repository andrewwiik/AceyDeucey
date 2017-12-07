#ifndef FindBetweenRanks_hpp
#define FindBetweenRanks_hpp

#include "Card.hpp"

class FindBetweenRanks {
public:
	FindBetweenRanks(Rank r1, Rank r2);
	bool operator()(const Card& card) const;
	
private:
	Rank highRank;
	Rank lowRank;
};


#endif
