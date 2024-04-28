#include "stdafx.h"
#include "characterTab.h"

characterTab::characterTab(sf::Font& font, sf::VideoMode& VM, Player& player) : Tab{ font,VM,player, false }, CharacterInfo{}
{
	//Background
	CharacterTabBack.setFillColor(sf::Color(50, 50, 50, 180));
	CharacterTabBack.setSize(sf::Vector2f{ GUI::p2pX(0.5f,VM), GUI::p2pY(1.f,VM) });
	CharacterTabBack.setPosition(sf::Vector2f{ 10,10 });
	//Text
	initText();
}

characterTab::~characterTab()
{
}

void characterTab::update()
{
	if (!hidden) {
		CharacterInfo.setString(player.CharacterTabString());
	}
}

void characterTab::render(sf::RenderTarget* target)
{
	if (!hidden) {
		target->draw(CharacterTabBack);
		//fix
		target->draw(CharacterInfo);
	}

}

void characterTab::initText()
{
	the_font.loadFromFile("Resources/Fonts/Halo3.ttf");
	CharacterInfo.setString(player.CharacterTabString());
	CharacterInfo.setFont(the_font);
	CharacterInfo.setCharacterSize(GUI::calccharsize(VM, 50));
	CharacterInfo.setFillColor(sf::Color::White);
	CharacterInfo.setPosition(CharacterTabBack.getPosition().x, CharacterTabBack.getPosition().y + 20.f);
}
