#include "stdafx.h"
#include "Tab.h"

Tab::Tab(sf::Font& font, sf::VideoMode& VM, Player& player, bool hidden): VM{VM},font{font}, player{player}, hidden{hidden}
{
	sf::Font temp{};
	if (!temp.loadFromFile("Resources/Fonts/Halo3.ttf")) {
		std::cout<<"Problem"<<std::endl;
	}

}

Tab::~Tab()
{
}

void Tab::togglehidden()
{
	hidden = !hidden;
}

const bool& Tab::getHidden() const
{
	return hidden;
}
