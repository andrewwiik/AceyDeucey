#include "Hand.hpp"
#include <vector>
#include <string>
#include <sstream>

Hand::Hand(Card &c1, Card &c2, BetDirection betDirect) {
	betDirection = betDirect;
	if (c1.rank > c2.rank) {
		high = c1;
		low = c2;
	} else {
		high = c2;
		low = c1;
	}
}

Hand::operator std::string() const {
	std::vector<std::string> lines(7);
	std::stringstream lowC = low;
	std::stringstream highC = high;
	std::stringstream thirdC = thirdCard;
	
	int x = 0;
	std::string line = "";
	
	while (std::getline(lowC, line)) {
		lines[x] += line;
		x++;
	}
	
	x = 0;
	while (std::getline(highC, line)) {
		lines[x] += line;
		x++;
	}
	
	x = 0;
	while (std::getline(thirdC, line)) {
		lines[x] += line;
		x++;
	}
	
	std::stringstream finalStream;
	
	for (auto s = lines.begin(); s != lines.end(); ++s) {
		finalStream << *s << std::endl;
	}
	
	return finalStream.str();
}

Hand::operator std::stringstream() const {
	return std::stringstream(static_cast<std::string>(*this));
}
