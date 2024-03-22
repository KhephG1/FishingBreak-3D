#include "stdafx.h"
#include "PauseMenu.h"
using namespace GUI;

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& fnt): font {fnt} 
{
	//init background
	background.setSize((sf::Vector2f)window.getSize());
	background.setFillColor(sf::Color{ 20, 20, 20, 100 });
	//init container
	container.setSize(sf::Vector2f{ window.getSize().x/4.f, (float)window.getSize().y - 60.f });
	container.setPosition(sf::Vector2f{ (window.getSize().x - container.getSize().x) / 2.f, 30.f });
	container.setFillColor(sf::Color{ 20,20,20,100 });
	//init text
	pmenuText.setFont(font);
	pmenuText.setFillColor(sf::Color{ 255,255,255 });
	pmenuText.setCharacterSize(30);
	pmenuText.setString("PAUSED");
	pmenuText.setPosition(container.getPosition().x + (container.getSize().x - pmenuText.getGlobalBounds().getSize().x)/2.0, container.getPosition().y + 40.f);
}

PauseMenu::~PauseMenu()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return buttons;
}

void PauseMenu::update(sf::Vector2f& MousePosition)
{
	for (auto but : buttons) {
		but.second->update(MousePosition);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& but : buttons) {
		but.second->render(&target);
	}

	target.draw(pmenuText);
}

void PauseMenu::addButton(const std::string key, const std::string text,float y)
{
	float width = 250;
	float x = container.getPosition().x + (container.getSize().x - width) / 2.f;
	buttons[key] = new Button{ x, y, 150, 50,text, &font, sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 255),sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50), sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0) };
}

const bool PauseMenu::isPressed(const std::string key)
{
	return buttons[key]->isPressed();
}
