#ifndef WelcomeScreen_hpp
#define WelcomeScreen_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <sstream>


class WelcomeScreen {
public:
	operator std::string() ;
	operator std::stringstream();
};

#endif
