#include "stdafx.h"
#include "GameState.h"

void GameState::initDifferedRender()
{
	render_tex.create(State_Data->gfxSettings->resolution.width, State_Data->gfxSettings->resolution.height);
	renderSprite.setTexture(render_tex.getTexture());
	renderSprite.setTextureRect(sf::IntRect{ 0,0 ,(int)State_Data->gfxSettings->resolution.width, (int)State_Data->gfxSettings->resolution.height });
}

void GameState::initView()
{
	MainView.setSize(sf::Vector2f{ (float)State_Data->gfxSettings->resolution.width, (float)State_Data->gfxSettings->resolution.height });
	MainView.setCenter(sf::Vector2f{ State_Data->gfxSettings->resolution.width / 2.f, State_Data->gfxSettings->resolution.height / 2.f });
}

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
	tMap = new TileMap{ State_Data->gridsize,100,100,"Resources/Images/Tiles/tiles.png" 
	};
	tMap->loadFromFile("text.txt");
}

GameState::GameState(StateData* state_data) : State{state_data}
{
	initDifferedRender();
	initView();
	initFonts();
	initTextures();
	initKeybinds();
	initPlayers();
	initPauseMenu();
	initTileMap();
	initPlayerGUI();
}

GameState::~GameState()
{
	delete player;
	delete tMap;
	delete playerGUI;
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
	updateMousePositions(&MainView);
	if (!paused) { //unpaused update
		updateView(dt);
		updatePlayerInput(dt);
		//ALWAYS:
		/*
		 Check for collisions -> move player
			NOT
		move player -> check for collisions
		-player movement depends on if it is colliding with a tile on the current frame
		*/
		updateTileMap(dt);//checks collisions
		if (player) {
			player->update(dt);//moves player
		}
		updatePlayerGUI(dt);
	}
	else {
		pmenu->update(mousePosWindow);
		updatePauseButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	render_tex.clear();
	render_tex.setView(MainView);
	tMap->render(render_tex, player->getGridPosition(static_cast<int>(State_Data->gridsize)),false);
	if (player) {
		player->hideHitbox(true);
		player->render(&render_tex);
	}
	tMap->DeferredRender(render_tex);
	//begin rendering gui using the default view (not dependant on where we are in map)
	render_tex.setView(window->getDefaultView());
	playerGUI->render(render_tex);
	if (paused) { //paused menu rendering
		
		pmenu->render(render_tex);
	}
	//FINAL RENDER
	render_tex.display();
	renderSprite.setTexture(render_tex.getTexture());
	target->draw(renderSprite);
}


void GameState::updatePlayerInput(const float& dt)
{
	//update player input
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT")))) {
		player->move(dt, -1.f, 0.f);
		if (getKeyTime()) {
			player->gainXP(10);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT")))) {
		player->move(dt, 1.f, 0.f);
		if (getKeyTime()) {
			player->loseXP(10);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP")))) {
		player->move(dt, 0.f, -1.f);
		if (getKeyTime())
			player->gainHP(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN")))) {
		player->move(dt, 0.f, 1.f);
		if(getKeyTime())
			player->loseHP(1);
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
	sf::VideoMode& vm = State_Data->gfxSettings->resolution;
	pmenu = new PauseMenu{ vm, fnt };
	pmenu->addButton("QUIT", "QUIT", p2pY(0.46,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));
}

void GameState::initPlayerGUI()
{
	playerGUI = new PlayerGUI{ player,State_Data->gfxSettings->resolution };
}

void GameState::updateTileMap(const float& dt)
{
	tMap->update();
	tMap->updateCollision(player,dt);
}

void GameState::updatePauseButtons()
{
	if (pmenu->isPressed("QUIT") && getKeyTime()) {
		endState();
	}
}

void GameState::updateView(const float& dt)
{
	//instead of moving the camera manually like in editor state, we set the camera to always follow the player
	//to avoid "tearing" which results from moving the camera using floating point values, we can use the floor function to reduce
	 
	MainView.setCenter(std::floor(player->getPosition().x +(float)(mousePosWindow.x - (float)State_Data->gfxSettings->resolution.width/2.f)/5.f ), 
		std::floor(player->getPosition().y + (float)(mousePosWindow.y - (float)State_Data->gfxSettings->resolution.height/2.f))/2.f);
}

void GameState::updatePlayerGUI(const float& dt)
{
	playerGUI->update(dt);
}
