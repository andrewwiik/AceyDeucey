#include "FindBetweenRanks.hpp"

FindBetweenRanks::FindBetweenRanks(Rank r1, Rank r2) {
	if (r1 > r2) {
		highRank = r1;
		lowRank = r2;
	} else {
		highRank = r2;
		lowRank = r1;
	}
}

bool FindBetweenRanks:: operator()(const Card& card) const {
	return card.rank > lowRank && card.rank < highRank;
}
