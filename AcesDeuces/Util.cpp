#include "Util.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>

int msleep(unsigned long milisec)
{
	struct timespec req={0};
	time_t sec=(int)(milisec/1000);
	milisec=milisec-(sec*1000);
	req.tv_sec=sec;
	req.tv_nsec=milisec*1000000L;
	while(nanosleep(&req,&req)==-1)
		continue;
	return 1;
}

void replaceStringWithString(std::string& subject, 
						const std::string& search,
						const std::string& replace) {

	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}


void alignStringToRight(std::string &string, int width) {
	int stringLength = int(string.length());
	if (stringLength < width)
		string = std::string(width - string.length(),' ') + string;
}

void alignStringToLeft(std::string &string, int width) {
	int stringLength = int(string.length());
	if (stringLength < width)
		string += std::string(width - string.length(),' ');
}

void alignStringToCenter(std::string& string, int width) {
	int stringLength = int(string.length());
	int spacesNeeded = width - stringLength;
	int eachSide = spacesNeeded/2;
	string = std::string(eachSide,' ') + string;
	string += std::string(eachSide + (spacesNeeded % 2 ? 1 : 0),' ');
}

std::string doubleToStringWithPrecision(double value, int precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << value;
	return stream.str();
}
