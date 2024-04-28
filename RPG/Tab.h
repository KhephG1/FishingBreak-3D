#pragma once

#include "Player.h"
#include "GUI.h"
class Tab
{
protected:
	sf::Font& font;
	sf::VideoMode& VM;
	Player& player;
	bool hidden;
public:
	Tab(sf::Font& font, sf::VideoMode& VM, Player& player, bool hidden);
	virtual~Tab();
	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target)= 0;
	void togglehidden();
	const bool& getHidden() const;
	
};

