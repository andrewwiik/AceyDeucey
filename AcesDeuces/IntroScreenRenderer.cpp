#include "IntroScreenRenderer.hpp"
#include "Util.hpp"
#include <vector>




void IntroScreenRenderer::renderScreen(int sleepFor) {
	
	std::vector<std::string> output(22);
	std::stringstream welcome = welcomeScreen;
	
	int x = 0;
	std::string line = "";
	
	while (std::getline(welcome, line)) {
		output[x] += line;
		x++;
		line = "";
	}
	
	for (auto s = output.begin(); s != output.end(); ++s) {
		std::cout << *s << std::endl;
	}
	
	std::cout.flush();
	if (sleepFor > 0) {
		std::cout.flush();
		msleep(sleepFor);
	}
}
