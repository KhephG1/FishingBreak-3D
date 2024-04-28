#include "stdafx.h"
#include "PlayerGUI.h"


void PlayerGUI::initFont()
{
	if (!font.loadFromFile("Resources/Fonts/Halo3.ttf"))
		throw std::runtime_error{ "PLAYER::GUI load font failed" };
}

void PlayerGUI::initLevelBar()
{
	float width = GUI::p2pX(0.026f,VM);

	float height = GUI::p2pY(0.046, VM);;
	float x = GUI::p2pX(0.01f,VM);
	float y = GUI::p2pY(0.148,VM);
	lvlBarOutline.setSize(sf::Vector2f(width, height));
	lvlBarOutline.setFillColor(sf::Color{ 0,255,10,200 });
	lvlBarOutline.setPosition(x, y);
	lvlBarOutline.setOutlineThickness(-2.f);
	lvlBarOutline.setOutlineColor(sf::Color::Red);
	lvlBarText.setFont(font);
	lvlBarText.setCharacterSize(GUI::calccharsize(VM,80));
	lvlBarText.setPosition(lvlBarOutline.getPosition().x + GUI::p2pX(0.00781,VM), lvlBarOutline.getPosition().y);
}

void PlayerGUI::initPlayerTabs(sf::VideoMode& vm, sf::Font& font, Player& player)
{
	guiTabs = new GuiTabs{ font,vm,player };
}



void PlayerGUI::initEXPBar()
{

	expBar = new GUI::ProgressBar{ 0.01f,0.0741f,0.156f,0.046f,player->getAttributeComponent()->expNext,VM,sf::Color::Blue,80,&font };
}

void PlayerGUI::inithpBar()
{
	//usually don't want to put local variables in functions called often since takes time
	hpBar = new GUI::ProgressBar{ 0.01f,0.0185f,0.156f,0.046f,player->getAttributeComponent()->hpMax,VM,sf::Color::Red,80,&font };

}

PlayerGUI::PlayerGUI(Player* plyr, sf::VideoMode& vm): player{plyr}, VM{vm}
{
	initFont();
	inithpBar();
	initEXPBar();
	initLevelBar();
	initPlayerTabs(vm,font,*plyr);
	//tabs
}

PlayerGUI::~PlayerGUI()
{
	delete hpBar;
	delete expBar;
	delete guiTabs;
}

void PlayerGUI::updatehpBar()
{
	hpBar->update(player->getAttributeComponent()->hp);

}

void PlayerGUI::updateEXPBar()
{
	expBar->setMaxVal(player->getAttributeComponent()->expNext);
	expBar->update(player->getAttributeComponent()->exp);
}

void PlayerGUI::updatelvlbar()
{
	lvlBarText.setString(std::to_string(player->getAttributeComponent()->level));
}

void PlayerGUI::updatePlayerTabs()
{
	guiTabs->update();
}


void PlayerGUI::renderhpBar(sf::RenderTarget& target)
{
	hpBar->render(target);

}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	expBar->render(target);
}

void PlayerGUI::renderlvlBar(sf::RenderTarget& target)
{
	target.draw(lvlBarOutline);
	target.draw(lvlBarText);
}

void PlayerGUI::renderPlayerTabs(sf::RenderTarget& target)
{
	guiTabs->render(&target);
}



void PlayerGUI::update(const float& dt)
{
	updatehpBar();
	updateEXPBar();
	updatelvlbar();
	updatePlayerTabs();

}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderhpBar(target);
	renderEXPBar(target);
	renderlvlBar(target);
	renderPlayerTabs(target);

	//Tabs

}

void PlayerGUI::toggleTabs()
{
	guiTabs->toggleTabs();
}

const bool PlayerGUI::getTabsOpen()
{
	return guiTabs->tabsOpen();
}
