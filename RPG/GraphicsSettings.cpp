#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicSettings::GraphicSettings() {
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	Vsync = false;
	frameRateLim = 120;
	contextset.antialiasingLevel = 0;
	videomodes = sf::VideoMode::getFullscreenModes();

}

void GraphicSettings::loadFromFile(const std::string path) {
	std::ifstream stream{ path };
	if (!stream.is_open()) {
		std::cout << "window failed" << std::endl;
	}
	if (stream.is_open()) {
		std::getline(stream, title);
		stream >> resolution.width >> resolution.height;
		stream >> fullscreen;
		stream >> frameRateLim;
		stream >> Vsync;
		stream >> contextset.antialiasingLevel;
	}
	stream.close();
}
void GraphicSettings::saveToFile(const std::string path) {
	std::ofstream stream{ path };
	if (!stream.is_open()) {
		std::cout << "window failed" << std::endl;
	}
	if (stream.is_open()) {
		stream << title;
		stream << resolution.width << resolution.height;
		stream << fullscreen;
		stream << frameRateLim;
		stream << Vsync;
		stream << contextset.antialiasingLevel;
	}
	stream.close();
}