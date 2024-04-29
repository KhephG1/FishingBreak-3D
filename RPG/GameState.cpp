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
	MainView.setSize(sf::Vector2f{ (float)State_Data->gfxSettings->resolution.width/2, (float)State_Data->gfxSettings->resolution.height/2 });
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
	if (!textures["BIRD1_SHEET"].loadFromFile("Resources/Images/Enemy/bird1_61x57.png")) {
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

void GameState::initEnemySystem()
{
	enemySystem = new EnemySystem{ activeEnemies, textures, *player };
}

GameState::GameState(StateData* state_data) : State{state_data}
{
	initPlayers();
	initDifferedRender();
	initSystems();
	initView();
	initFonts();
	initTextures();
	initKeybinds();
	
	initPauseMenu();
	initShaders();
	initEnemySystem();
	initTileMap();
	initPlayerGUI();
	

}

GameState::~GameState()
{
	delete player;
	delete tMap;
	delete playerGUI;
	delete enemySystem;
	delete tts;
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
		
		updatePlayer(dt);
		updateEnemies(dt);
		tts->update(dt);
		playerGUI->updatePlayerTabs();

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
	tMap->render(render_tex, player->getGridPosition(static_cast<int>(State_Data->gridsize)),false,player->getCenter(), &core_shader);
	if (player) {
		player->hideHitbox(true);
	
		player->render(&render_tex, &core_shader, false, player->getCenter());
	}
	for (auto* i : activeEnemies) {
			i->render(&render_tex, &core_shader, true, player->getCenter());
	}
	tMap->DeferredRender(render_tex,player->getCenter(),&core_shader);
	tts->render(&render_tex);
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
	if (!playerGUI->getTabsOpen()) {
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

void GameState::initSystems()
{
	tts = new TextTagSystem("Resources/Fonts/Halo3.ttf");
}

void GameState::updateTileMap(const float& dt)
{
	tMap->updateWorldBoundsCollision(player, dt);
	tMap->updateTileCollision(player,dt);
	tMap->updateTiles(player,dt, *enemySystem);

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
	if (!playerGUI->getTabsOpen()) {
		MainView.setCenter(std::floor(player->getPosition().x + (float)(mousePosWindow.x - (float)State_Data->gfxSettings->resolution.width / 4.f) / 2.f),
			std::floor(player->getPosition().y + (float)(mousePosWindow.y - (float)State_Data->gfxSettings->resolution.height/4.f)/2.f));
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
}

void GameState::updatePlayerGUI(const float& dt)
{
	playerGUI->update(dt);
	if (player->getPosition().x < 0 || player->getPosition().y < 0) {

		
		player->setPosition(400, 400);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key{ (sf::Keyboard::Key)keybinds.at("OPEN_CHARACTER_TAB") })) {
		playerGUI->toggleTabs();
	}
}

void GameState::updatePlayer(const float& dt)
{
	if (player) {
		player->update(dt, mousePosView);//moves player
	}
	updatePlayerGUI(dt);
}

void GameState::updateEnemies(const float& dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&& player->getWeapon()->getattackTimer()){
		player->setinitAttack(true);
	}
	int index = 0;
	for (auto* enemy : activeEnemies) {
		enemy->update(dt, mousePosView);
		tMap->updateWorldBoundsCollision(enemy, dt);
		tMap->updateTileCollision(enemy, dt);
		updateCombat(enemy,index, dt);
		if (enemy->dead()) {
			player->gainXP(enemy->getGainExp());
			player->gainHP(enemy->getAttributeComponent()->hpMax / 2);
			tts->createTextTagString(EXPERIENCE, player->getCenter().x, player->getCenter().y,(int)enemy->getGainExp(),"+","XP");
			enemySystem->removeEnemy(index);
			--index;
		}
		++index;
	}
	player->setinitAttack(false);

}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && enemy->getGlobalBounds().contains(mousePosView)&&player->getDistance(enemy) < player->getWeapon()->getRange()&&player->getInitAttack()&&enemy->getDamageTimerDone()) {
		
			tts->createTextTagString(NEGATIVE, player->getCenter().x, player->getCenter().y, (int)player->getDamage(), "-", "HP");
			enemy->damage(player->getDamage());
			enemy->resetDamageTimer();
			
	}
	if (enemy->getGlobalBounds().intersects(player->getGlobalBounds())&&player->getDamageTimer()) {
		int dmg = enemy->getAttributeComponent()->damageMax;
		player->loseHP(dmg);
		tts->createTextTagString(TagTypes::DEFAULT_TYPE, enemy->getPosition().x, enemy->getPosition().y, dmg, "-", "HP");
	}
	if (player->getAttributeComponent()->hp <= 0) {
		quit = true;
	}
	
}
