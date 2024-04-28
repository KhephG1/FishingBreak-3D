#pragma once

#include "characterTab.h"


enum PLAYER_TABS {CHARACTER_TAB, INVENTORY_TAB};
class GuiTabs
{
private:
	std::vector<Tab*> tabs;
	//Tabs

	sf::Font& font;
	sf::VideoMode& VM;
	Player& player;
	sf::Clock keyTimer;
	float keytimeMax;
public:
	GuiTabs(sf::Font& font, sf::VideoMode& VM, Player& player);
	virtual ~GuiTabs();
	void updateCharacterTab();
	void update();
	void render(sf::RenderTarget* target);
	const bool getKeyTime();
	const bool tabsOpen();
	void toggleTabs();
	void initTabs();
};

