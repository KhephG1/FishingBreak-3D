#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H
class GraphicSettings {
private:
public:
	GraphicSettings();
	sf::VideoMode resolution;
	bool fullscreen;
	bool Vsync;
	std::string title;
	unsigned frameRateLim;
	sf::ContextSettings contextset;
	std::vector<sf::VideoMode> videomodes;
	void loadFromFile(const std::string path);
	void saveToFile(const std::string path);
};
#endif