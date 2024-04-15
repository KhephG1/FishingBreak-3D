#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!font.loadFromFile("Resources/Fonts/Halo3.ttf"))
		throw std::runtime_error{ "PLAYER::GUI load font failed" };
}

void PlayerGUI::initLevelBar()
{
	float width = 50.f;
	float height = 50.f;
	float x = 20.f;
	float y = 160.f;
	lvlBarOutline.setSize(sf::Vector2f(width, height));
	lvlBarOutline.setFillColor(sf::Color{ 0,255,10,200 });
	lvlBarOutline.setPosition(x, y);
	lvlBarOutline.setOutlineThickness(-2.f);
	lvlBarOutline.setOutlineColor(sf::Color::Red);
	lvlBarText.setFont(font);
	lvlBarText.setCharacterSize(40);
	lvlBarText.setPosition(lvlBarOutline.getPosition().x + 15.f, lvlBarOutline.getPosition().y);
}

void PlayerGUI::initEXPBar()
{
	//usually don't want to put local variables in functions called often since takes time
	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 80.f;
	ExpBarMaxWidth = width;
	expBarOutline.setSize(sf::Vector2f(width, height));
	expBarFill.setFillColor(sf::Color{ 250,0,20,200 });
	expBarOutline.setFillColor(sf::Color{ 100,100,100,200 });
	expBarOutline.setPosition(x, y);
	expBarFill.setSize(expBarOutline.getSize());
	expBarFill.setPosition(expBarOutline.getPosition());
	expBarText.setFont(font);
	expBarText.setPosition(expBarOutline.getPosition().x + 10.f, expBarOutline.getPosition().y + 10.f);
}

void PlayerGUI::inithpBar()
{
	//usually don't want to put local variables in functions called often since takes time
	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;
	hpBarMaxWidth = width;
	hpBarOutline.setSize(sf::Vector2f(width, height));
	hpBarFill.setFillColor(sf::Color{ 250,0,20,200 });
	hpBarOutline.setFillColor(sf::Color{ 100,100,100,200 });
	hpBarOutline.setPosition(x, y);
	hpBarFill.setSize(hpBarOutline.getSize());
	hpBarFill.setPosition(hpBarOutline.getPosition());
	hpBarText.setFont(font);
	hpBarText.setPosition(hpBarOutline.getPosition().x + 10.f, hpBarOutline.getPosition().y + 10.f);

}

PlayerGUI::PlayerGUI(Player* plyr): player{plyr}
{
	initFont();
	inithpBar();
	initEXPBar();
	initLevelBar();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::updatehpBar()
{
	float percent = static_cast<float>(player->getAttributeComponent()->hp) / static_cast<float>(player->getAttributeComponent()->hpMax);
	hpBarFill.setSize(sf::Vector2f{ hpBarMaxWidth * percent, hpBarFill.getSize().y });
	hpBarText.setString(std::to_string(player->getAttributeComponent()->hp) + "/" + std::to_string(player->getAttributeComponent()->hpMax));

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
	target.draw(hpBarOutline);
	target.draw(hpBarFill);
	target.draw(hpBarText);

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
