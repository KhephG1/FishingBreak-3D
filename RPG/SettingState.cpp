#include "stdafx.h"
#include "SettingState.h"

SettingState::~SettingState()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}

	for (auto iter = dropdownL.begin(); iter != dropdownL.end(); ++iter) {
		delete iter->second;
	}

}
SettingState::SettingState(StateData* state_data) : State{state_data} {
	initVariables();
	initBackgrounds();
	initKeybinds();
	initFonts();
	initGUI();
	initText();
}


void SettingState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackgrounds()
{
	if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/menu_background.png")) {
		throw std::invalid_argument{ "failed to load texture" };
	}
	background.setSize((sf::Vector2f)window->getSize());
	background.setTexture(&backgroundTexture);
}

void SettingState::initKeybinds()
{
	std::ifstream stream("Config/game_state_keybinds.txt", std::ios::in);
	if (!stream.is_open()) {
	}
	if (stream.is_open()) {
		std::string operation{};
		std::string key{};
		while (stream >> operation >> key) {
			std::cout << operation << " " << key << std::endl;
			keybinds[operation] = supportedKeys->at(key);
		}
	}
	stream.close();

}

void SettingState::initFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Halo3.ttf")) {
		throw std::runtime_error{ "could not load font" };
	}
}

void SettingState::initGUI()
{
	buttons["EXIT_STATE"] = new Button{ 100, 675, 150, 50,"Back", &font,  sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };

	buttons["APPLY"] = new Button{ 100, 600, 150, 50,"Apply", &font,  sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
	std::vector<std::string> a_list{ "1920x1080", "800x600", "640x480"};
	std::vector<std::string> modes_str;

	for (auto& i : modes) {
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	dropdownL["RESOLUTION"] = new GUI::DropDownList(300, 600, 200, 50, font, modes_str,0);
}

void SettingState::initText()
{
	optionsText.setFont(font);
	optionsText.setPosition(100, 500);
	optionsText.setCharacterSize(28);
	optionsText.setFillColor( sf::Color::White );
	optionsText.setString("Resolution \nVsync \nAntialiasing \n");
}


void SettingState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);
	updateGUI(dt);
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);

	renderGUI(target);

	target->draw(optionsText);

	sf::Text mouseText;
	mouseText.setPosition(mousePosView);
	mouseText.setFont(font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(mousePosView.x) + "," + std::to_string(mousePosView.y));
	target->draw(mouseText);
	
}



void SettingState::updateInput(const float& dt)
{
	//update player input

}

void SettingState::updateGUI(const float& dt)
{
	for (auto but : buttons) {
		but.second->update(mousePosView);
	}
	
	//quit game
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}

	//Apply selected settings

	if (buttons["APPLY"]->isPressed()) {
		State_Data->gfxSettings->resolution = modes[dropdownL["RESOLUTION"]->getlistID()];
		window->create(State_Data->gfxSettings->resolution, State_Data->gfxSettings->title, sf::Style::Default);
	}

	//dropdownlists


	//dropdownlists functionality

	for (auto& it : dropdownL) {
		it.second->update(mousePosView, dt);
	}
}

void SettingState::renderGUI(sf::RenderTarget* target)
{

	for (auto but : buttons) {
		but.second->render(target);
	}

	for (auto& it : dropdownL) {
		it.second->render(target);
	}
}