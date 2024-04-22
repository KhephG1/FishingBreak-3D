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

	if (!textures["RAT1_SHEET"].loadFromFile("Resources/Images/Enemy/rat1_60x64.png")) {
		throw std::runtime_error{ "ERROR::GAME_STATE::COULD_NOT_LOAD_RAT1_TEXTURE" };
	}
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
	player = new Player{ 400, 400, &textures["PLAYER_SHEET"] };

}

void GameState::initTileMap()
{

	tMap = new TileMap{ State_Data->gridsize,100,100,"Resources/Images/Tiles/tiles.png" };
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
	initShaders();
	initTileMap();
	initPlayerGUI();
	activeEnemies.push_back(new Rat{ 200.f,100.f,&textures["RAT1_SHEET"] });
	activeEnemies.push_back(new Rat{ 500.f,200.f,&textures["RAT1_SHEET"] });
	activeEnemies.push_back(new Rat{ 600.f,300.f,&textures["RAT1_SHEET"] });
	activeEnemies.push_back(new Rat{ 200.f,400.f,&textures["RAT1_SHEET"] });
}

GameState::~GameState()
{
	delete player;
	delete tMap;
	delete playerGUI;

	for (size_t i = 0; i < activeEnemies.size(); i++) {
		delete activeEnemies.at(i);
	}

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
			player->update(dt,mousePosView);//moves player
		}
		updatePlayerGUI(dt);
		
	}
	else {
		pmenu->update(mousePosWindow);
		updatePauseButtons();
	}
	for (auto* i : activeEnemies) {
		i->update(dt, mousePosView);
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	render_tex.clear();
	render_tex.setView(MainView);
	tMap->render(render_tex, player->getGridPosition(static_cast<int>(State_Data->gridsize)),false,player->getCenter(), &core_shader);
	if (player) {
		player->hideHitbox(true);
	
		player->render(&render_tex, &core_shader, false, player->getCenter());
	}
	tMap->DeferredRender(render_tex,player->getCenter(),&core_shader);
	//begin rendering gui using the default view (not dependant on where we are in map)
	render_tex.setView(window->getDefaultView());
	playerGUI->render(render_tex);
	if (paused) { //paused menu rendering
		
		pmenu->render(render_tex);
	}
	//FINAL RENDER
	for (auto* i : activeEnemies) {
		i->render(&render_tex, &core_shader, true, player->getCenter());
	}
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

void GameState::initShaders()
{
	//see book of shaders.com for how shaders work
	//shaders use GPU --> calculated in parallel (CPU calculates one at a time
	if (!core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag")) {
		std::cout<<"ERROR::GAMESTATE::COULDNOTLOADSHADER"<<std::endl;
	}
}

void GameState::updateTileMap(const float& dt)
{
	
	tMap->update(player,dt);
	for (auto* i : activeEnemies) {
		tMap->update(i, dt);
	}
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
	if (tMap->getMaxSizeFloat().x >= MainView.getSize().x)
	{
		if (MainView.getCenter().x - MainView.getSize().x / 2.f < 0.f)
		{
			MainView.setCenter(0.f + MainView.getSize().x / 2.f, MainView.getCenter().y);
		}
		else if (MainView.getCenter().x + MainView.getSize().x / 2.f > tMap->getMaxSizeFloat().x)
		{
			MainView.setCenter(this->tMap->getMaxSizeFloat().x - MainView.getSize().x / 2.f, MainView.getCenter().y);
		}
	}

	if (this->tMap->getMaxSizeFloat().y >= MainView.getSize().y)
	{
		if (MainView.getCenter().y - MainView.getSize().y / 2.f < 0.f)
		{
			MainView.setCenter(MainView.getCenter().x, 0.f + MainView.getSize().y / 2.f);
		}
		else if (MainView.getCenter().y + MainView.getSize().y / 2.f > tMap->getMaxSizeFloat().y)
		{
			MainView.setCenter(MainView.getCenter().x, this->tMap->getMaxSizeFloat().y - MainView.getSize().y / 2.f);
		}
	}

	ViewGridPosition.x = static_cast<int>(MainView.getCenter().x) / static_cast<int>(State_Data->gridsize);
	ViewGridPosition.y = static_cast<int>(MainView.getCenter().y) / static_cast<int>(this->State_Data->gridsize);
}

void GameState::updatePlayerGUI(const float& dt)
{
	playerGUI->update(dt);
	if (player->getPosition().x < 0 || player->getPosition().y < 0) {

		std::cout << "setting position GUI" << std::endl;
		player->setPosition(400, 400);
	}
}
