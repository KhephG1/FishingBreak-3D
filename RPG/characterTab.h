#pragma once
#include "Tab.h"
class characterTab: public Tab
{
private:
	sf::RectangleShape CharacterTabBack;
	sf::Text CharacterInfo;
	sf::Font the_font;
public:
	characterTab(sf::Font& font, sf::VideoMode& VM,Player& player);
	virtual~characterTab();
	void update();
	void render(sf::RenderTarget* target);
	void initText();
	
};

