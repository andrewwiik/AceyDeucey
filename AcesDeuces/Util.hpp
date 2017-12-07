#ifndef Util_hpp
#define Util_hpp

#include <stdio.h>
#include <string>

int msleep(unsigned long milisec);
void replaceStringWithString(std::string& subject, 
						const std::string& search,
						const std::string& replace);

void alignStringToRight(std::string& string, int width);
void alignStringToLeft(std::string& string, int width);
void alignStringToCenter(std::string& string, int width);

std::string doubleToStringWithPrecision(double value, int precision);

#endif
