#ifndef IntroScreenRenderer_hpp
#define IntroScreenRenderer_hpp

#include <stdio.h>
#include "WelcomeScreen.hpp"

class IntroScreenRenderer {
public:
	void renderScreen(int sleepFor = 0);
private:
	WelcomeScreen welcomeScreen;
};

#endif
