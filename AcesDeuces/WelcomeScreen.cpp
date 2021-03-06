#include "WelcomeScreen.hpp"

WelcomeScreen::operator std::string() {
	std::string str = "";
	str +="  /$$$$$$\n"
		" /$$__  $$\n"
		"| $$  \\ $$  /$$$$$$$  /$$$$$$  /$$   /$$\n"
		"| $$$$$$$$ /$$_____/ /$$__  $$| $$  | $$\n"
		"| $$__  $$| $$      | $$$$$$$$| $$  | $$\n"
		"| $$  | $$| $$      | $$_____/| $$  | $$\n"
		"| $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$$\n"
		"|__/  |__/ \\_______/ \\_______/ \\____  $$\n"
		"                               /$$  | $$\n"
		" /$$$$$$$                     |  $$$$$$/\n"
		"| $$__  $$                     \\______/\n"
		"| $$  \\ $$  /$$$$$$  /$$   /$$  /$$$$$$$  /$$$$$$  /$$   /$$\n"
		"| $$  | $$ /$$__  $$| $$  | $$ /$$_____/ /$$__  $$| $$  | $$\n"
		"| $$  | $$| $$$$$$$$| $$  | $$| $$      | $$$$$$$$| $$  | $$\n"
		"| $$  | $$| $$_____/| $$  | $$| $$      | $$_____/| $$  | $$\n"
		"| $$$$$$$/|  $$$$$$$|  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$\n"
		"|_______/  \\_______/ \\______/  \\_______/ \\_______/ \\____  $$\n"
		"                                                   /$$  | $$\n"
		"By Andrew Wiik, Alexander Socha,                  |  $$$$$$/\n"
		"    Bryan Waltman, Abdullah Fahad                  \\______/\n";
	return str;
}

WelcomeScreen::operator std::stringstream() {
	return std::stringstream(static_cast<std::string>(*this));
}
