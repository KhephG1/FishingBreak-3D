#pragma once
#include "player.h"
#include "GUI.h"
class PlayerGUI
{
private:

	Player* player;
	sf::Font font;
	sf::VideoMode& VM;

	//HP
	sf::Text hpBarText;
	sf::RectangleShape hpBarOutline;
	sf::RectangleShape hpBarFill;
	float hpBarMaxWidth;
	

	//EXP
	std::string expBarstring;
	sf::Text expBarText;
	float ExpBarMaxWidth;
	sf::RectangleShape expBarOutline;
	sf::RectangleShape expBarFill;

	//Level
	std::string lvlBarstring;
	sf::Text lvlBarText;
	sf::RectangleShape lvlBarOutline;
	//Functions
	void initEXPBar();
	void inithpBar();
	void initFont();
	void initLevelBar();


public:
	PlayerGUI(Player* plyr, sf::VideoMode& vm);
	virtual ~PlayerGUI();
	//Functions
	void updatehpBar();
	void updateEXPBar();
	void updatelvlbar();
	void renderhpBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderlvlBar(sf::RenderTarget& target);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

