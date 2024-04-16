#include "stdafx.h"
#include "MainMenuState.h"
#include "GraphicsSettings.h"
void MainMenuState::initVariables()
{
}



void MainMenuState::initKeybinds()
{
	std::ifstream stream("Config/game_state_keybinds.txt", std::ios::in);
	if (!stream.is_open()) {
	}
	if (stream.is_open()) {
		std::string operation{};
		std::string key{};
		while (stream >> operation >> key) {
			
			keybinds[operation] = supportedKeys->at(key);
		}
	}
	stream.close();

}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Halo3.ttf")) {
		throw std::runtime_error{ "could not load font" };
	}
}

void MainMenuState::initGUI()
{
	//the constructor arguments represent the following properties:
	/*
	Button pos x
	Button pos y
	Button width
	Button height
	Button name
	font
	idle border color
	hover border color
	active border color
	idle text color
	hover text color
	active text color

	idle text background
	hover text background
	active text background

	since you actually can't see active, it is left as blue
	*/
	sf::VideoMode& vm = State_Data->gfxSettings->resolution;
	buttons["EXIT_STATE"] = new Button{ p2pX(0.072,vm), p2pY(0.278,vm), p2pX(0.0781,vm), p2pY(0.0416,vm),vm,"Quit", &font, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
	buttons["GAME_STATE"] = new Button{ p2pX(0.187,vm),p2pY(0.278,vm),  p2pX(0.0781,vm), p2pY(0.0416,vm),vm,"New Game", &font,  sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
	buttons["EDITOR_STATE"] = new Button{ p2pX(0.39,vm),p2pY(0.278,vm),  p2pX(0.0781,vm), p2pY(0.0416,vm),vm,"Editor", &font,   sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
	buttons["SETTING_STATE"] = new Button{ p2pX(0.286,vm),p2pY(0.278,vm),  p2pX(0.0781,vm), p2pY(0.0416,vm),vm,"Setting", &font,   sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
	//Background
	if (!backgroundTexture.loadFromFile("Resources/Images/Backgrounds/menu_background.png")) {
		throw std::invalid_argument{ "failed to load texture" };
	}
	background.setSize((sf::Vector2f)window->getSize());
	background.setTexture(&backgroundTexture);
}

MainMenuState::MainMenuState(StateData* state_data) : State(state_data){
	initVariables();
	
	initKeybinds();
	initFonts();
	initGUI();

}

MainMenuState::~MainMenuState()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}
}

void MainMenuState::update(const float& dt)
{
	
	updateMousePositions(nullptr);
	updateInput(dt);
	updateButtons();
	
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);
	
	renderButtons(target);
	sf::Text mouseText;
	mouseText.setPosition(mousePosView);
	mouseText.setFont(font);
	mouseText.setCharacterSize(12);
	mouseText.setString(std::to_string(mousePosView.x) + "," + std::to_string(mousePosView.y));
	target->draw(mouseText);
}



void MainMenuState::updateInput(const float& dt)
{
	//update player input
}

void MainMenuState::updateButtons()
{
	for (auto but : buttons) {
		but.second->update(mousePosWindow);
	}
	//New Game
	if (buttons["GAME_STATE"]->isPressed()) {
		states->push(new GameState{State_Data });
	}
	//Settings
	if (buttons["SETTING_STATE"]->isPressed()) {
		states->push(new SettingState{ State_Data });
	}
	//editor
	if (buttons["EDITOR_STATE"]->isPressed()) {
		states->push(new Editor_State{ State_Data });
	}
	//quit game
	if (buttons["EXIT_STATE"]->isPressed()) {
		endState();
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	
	for (auto but : buttons) {
		but.second->render(target);
	}
}

void MainMenuState::resetGUI()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}
	buttons.clear();
	initGUI();
}
