#pragma once
#include "GuiTabs.h"
class PlayerGUI
{
private:

	Player* player;
	sf::Font font;
	sf::VideoMode& VM;

	//HP
	GUI::ProgressBar* hpBar;
	

	//EXP
	GUI::ProgressBar* expBar;

	//Level
	std::string lvlBarstring;
	sf::Text lvlBarText;
	sf::RectangleShape lvlBarOutline;

	GuiTabs* guiTabs;

	//Functions
	void initEXPBar();
	void inithpBar();
	void initFont();
	void initLevelBar();
	void initPlayerTabs(sf::VideoMode& vm,sf::Font& font, Player& player);

public:
	PlayerGUI(Player* plyr, sf::VideoMode& vm);
	virtual ~PlayerGUI();
	//Functions
	void updatehpBar();
	void updateEXPBar();
	void updatelvlbar();
	void updatePlayerTabs();
	void renderhpBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderlvlBar(sf::RenderTarget& target);
	void renderPlayerTabs(sf::RenderTarget& target);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
	void toggleTabs();
	//Accessor
	const bool getTabsOpen();
};

