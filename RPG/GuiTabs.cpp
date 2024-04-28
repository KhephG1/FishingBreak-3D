#include "stdafx.h"
#include "GuiTabs.h"



GuiTabs::GuiTabs(sf::Font& fnt, sf::VideoMode& vm, Player& the_player): font{fnt},VM{vm}, player{the_player}
{
	initTabs();
	keytimeMax = 1.0f;
	keyTimer.restart();
}

GuiTabs::~GuiTabs()
{
}

void GuiTabs::updateCharacterTab()
{
}

void GuiTabs::update()
{
	for (auto i : tabs) {
		if(!i->getHidden())
			i->update();
	}
}

void GuiTabs::render(sf::RenderTarget* target)
{
	for (auto i : tabs) {
		if(!i->getHidden())
			i->render(target);
	}
	

}

const bool GuiTabs::getKeyTime()
{
	if (keyTimer.getElapsedTime().asSeconds() >= keytimeMax) {
		keyTimer.restart();
		return true;
	}

	return false;
}

const bool GuiTabs::tabsOpen()
{
	for (auto tab : tabs) {
		if (!tab->getHidden()) {
			return true;
		}
	}
	return false;
}

void GuiTabs::toggleTabs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && getKeyTime()) {
		
		tabs.at(CHARACTER_TAB)->togglehidden();
	}

}

void GuiTabs::initTabs()
{
	tabs.push_back(new characterTab{ font,VM,player });
}
