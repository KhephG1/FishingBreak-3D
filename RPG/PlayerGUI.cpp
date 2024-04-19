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

void PlayerGUI::initEXPBar()
{
	//usually don't want to put local variables in functions called often since takes time
	float width = GUI::p2pX(0.156f, VM);;
	float height = GUI::p2pY(0.046f, VM);;
	float x = GUI::p2pX(0.01f,VM);
	float y = GUI::p2pY(0.0741f,VM);
	ExpBarMaxWidth = width;
	expBarOutline.setSize(sf::Vector2f(width, height));
	expBarFill.setFillColor(sf::Color{ 250,0,20,200 });
	expBarOutline.setFillColor(sf::Color{ 100,100,100,200 });
	expBarOutline.setPosition(x, y);
	expBarFill.setSize(expBarOutline.getSize());
	expBarFill.setPosition(expBarOutline.getPosition());
	expBarText.setCharacterSize(GUI::calccharsize(VM, 80));
	expBarText.setFont(font);
	expBarText.setPosition(expBarOutline.getPosition().x + GUI::p2pX(0.0052,VM), expBarOutline.getPosition().y + GUI::p2pY(0.00925,VM));
}

void PlayerGUI::inithpBar()
{
	//usually don't want to put local variables in functions called often since takes time
	float width = GUI::p2pX(0.156f,VM);
	float height = GUI::p2pY(0.046f,VM);
	float x = GUI::p2pX(0.01f,VM);
	float y = GUI::p2pY(0.0185f,VM)
		;
	hpBar = new GUI::ProgressBar{ 0.01f,0.0185f,0.156f,0.046f,player->getAttributeComponent()->hpMax,VM,&font };

}

PlayerGUI::PlayerGUI(Player* plyr, sf::VideoMode& vm): player{plyr}, VM{vm}
{
	initFont();
	inithpBar();
	initEXPBar();
	initLevelBar();
}

PlayerGUI::~PlayerGUI()
{
	delete hpBar;
}

void PlayerGUI::updatehpBar()
{
	hpBar->update(player->getAttributeComponent()->hp);

}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(player->getAttributeComponent()->exp) / static_cast<float>(player->getAttributeComponent()->expNext);
	expBarFill.setSize(sf::Vector2f{ ExpBarMaxWidth * percent, expBarFill.getSize().y });
	expBarText.setString(std::to_string(player->getAttributeComponent()->exp) + "/" + std::to_string(player->getAttributeComponent()->expNext));
}

void PlayerGUI::updatelvlbar()
{
	lvlBarText.setString(std::to_string(player->getAttributeComponent()->level));
}

void PlayerGUI::renderhpBar(sf::RenderTarget& target)
{
	hpBar->render(target);

}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(expBarOutline);
	target.draw(expBarFill);
	target.draw(expBarText);
}

void PlayerGUI::renderlvlBar(sf::RenderTarget& target)
{
	target.draw(lvlBarOutline);
	target.draw(lvlBarText);
}

void PlayerGUI::update(const float& dt)
{
	updatehpBar();
	updateEXPBar();
	updatelvlbar();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	renderhpBar(target);
	renderEXPBar(target);
	renderlvlBar(target);
}
