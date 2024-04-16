
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GUI.h"

using namespace GUI;
class PauseMenu
{
public:
	PauseMenu(sf::VideoMode& vm, sf::Font& fnt);
	virtual ~PauseMenu();
	std::map<std::string, Button*>& getButtons();
	 sf::VideoMode& VM;
	void update(sf::Vector2i& MousePosition);
	void render(sf::RenderTarget& target);
	void addButton(const std::string key, const std::string text,const float y,const float width, const float height);
	const bool isPressed(const std::string key);
private:
	sf::Font& font;
	sf::Text pmenuText;
	sf::RectangleShape container;
	sf::RectangleShape background;

	std::map<std::string, Button*> buttons;
};

#endif