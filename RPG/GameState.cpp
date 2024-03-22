#include "stdafx.h"
#include "GameState.h"

void GameState::initTextures()
{
	sf::Texture temp{};

	if (!temp.loadFromFile("Resources/Images/player/player_sheet.png")) {
		throw std::runtime_error{ "ERROR" };
	}
	textures["PLAYER_SHEET"] = temp;
}

void GameState::initKeybinds()
{
	std::ifstream stream("Config/game_state_keybinds.txt",std::ios::in);
	if (!stream.is_open()) {
	}
	if (stream.is_open()) {
		std::string operation{};
		std::string key{};
		while(stream>>operation>>key) {
			std::cout << operation << " " << key << std::endl;
			keybinds[operation] = supportedKeys->at(key);
		}
	}
	stream.close();

}

void GameState::initPlayers()
{
	player = new Player{ 0, 0, &textures["PLAYER_SHEET"] };
}

void GameState::initTileMap()
{
	tMap = new TileMap{ State_Data->gridsize,10,10 };
}

GameState::GameState(StateData* state_data) : State{state_data}
{
	initFonts();
	initTextures();
	initKeybinds();
	initPlayers();
	initPauseMenu();
	initTileMap();
}

GameState::~GameState()
{
	delete player;
	delete tMap;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE")))&& getKeyTime()) {
		if (!paused) {
			pauseState();
		}
		else {
			unpauseState();
		}
	}
}

void GameState::update(const float& dt)
{
	updateKeyTime(dt);
	updateInput(dt);
	updateMousePositions();
	if (!paused) { //unpaused update
		updatePlayerInput(dt);
		if (player) {
			player->update(dt);
		}
	}
	else {
		pmenu->update(mousePosView);
		updatePauseButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	tMap->render(*target);
	if (player) {
		player->render(target);
	}
	if (paused) { //paused menu rendering
		pmenu->render(*target);
	}
}


void GameState::updatePlayerInput(const float& dt)
{
	//update player input
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))) {
		player->move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))) {
		player->move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) {
		player->move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) {
		player->move(dt, 0.f, 1.f);
	}
	
	
}

void GameState::initFonts()
{
	if (!fnt.loadFromFile("Resources/Fonts/Halo3.ttf")) {
		throw std::runtime_error{ "could not load font" };
	}
}

void GameState::initPauseMenu()
{
	pmenu = new PauseMenu{ *window, fnt };
	pmenu->addButton("QUIT", "QUIT", 500.f);
}

void GameState::updatePauseButtons()
{
	if (pmenu->isPressed("QUIT") && getKeyTime()) {
		endState();
	}
}
