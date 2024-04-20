#include "stdafx.h"
#include "Editor_State.h"

void Editor_State::initVariables()
{
	camera_speed = 1000.f;
}

void Editor_State::initEditorStateData()
{
	EditorStatedata.keybinds = &keybinds;
	EditorStatedata.view = &MainView;
	EditorStatedata.font = &font;
	EditorStatedata.keyTime = &keyTime;
	EditorStatedata.keyTimeMax = &keyTimeMax;
	EditorStatedata.mousePosGrid = &mousePosGrid;
	EditorStatedata.mousePosScreen= &mousePosScreen;
	EditorStatedata.mousePosView = &mousePosView;
	EditorStatedata.mousePosWindow = &mousePosWindow;
	


}


void Editor_State::initPauseMenu()
{
	sf::VideoMode& vm = State_Data->gfxSettings->resolution;
	pmenu = new PauseMenu{vm, font };
	pmenu->addButton("QUIT", "QUIT", p2pY(0.46f,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));
	pmenu->addButton("SAVE", "SAVE", p2pY(0.65f,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));
	pmenu->addButton("LOAD", "LOAD", p2pY(0.556f,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));

}

void Editor_State::initKeybinds()
{
	//std::ios::in is a flag that opens the file for the purpose of reading
	//we are reading the preset keybinds for the editor state from a file 
	std::ifstream stream("Config/editor_state_keybinds.txt", std::ios::in);
	if (!stream.is_open()) {
		throw std::runtime_error{ "error" };
	}else{
		std::string operation{};
		std::string key{};
		while (stream >> operation >> key) {
			std::cout << operation << " " << key << std::endl;
			keybinds[operation] = supportedKeys->at(key);
		}
	}
	stream.close();

}

void Editor_State::initFonts()
{
	if (!font.loadFromFile("Resources/Fonts/Halo3.ttf")) {
		throw std::runtime_error{ "could not load font" };
	}
}


void Editor_State::initButtons()
{
	buttons["HIDE"] =new Button{30,(float)State_Data->gfxSettings->resolution.height - 50 , 150, 30,State_Data->gfxSettings->resolution,"HIDE SELECTOR", &font, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent};
}

void Editor_State::initTileMap()
{
	map = new TileMap{ State_Data->gridsize, 100,100, "Resources/Images/Tiles/tiles.png"};
}

void Editor_State::updateEditorInput(const float& dt)
{
	//Adding tiles to tilemap
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAM_UP")))) {
		MainView.move(0.f, -camera_speed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAM_DOWN")))) {
		MainView.move(0.f, camera_speed * dt);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAM_RIGHT")))) {
		MainView.move(camera_speed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAM_LEFT")))) {
		MainView.move(-camera_speed * dt, 0.f);
	}
	
}

void Editor_State::initGUI()
{

}

void Editor_State::initView()
{
	MainView.setSize(sf::Vector2f{ (float)State_Data->gfxSettings->resolution.width, (float)State_Data->gfxSettings->resolution.height });
	MainView.setCenter(State_Data->gfxSettings->resolution.width / 2.f, State_Data->gfxSettings->resolution.height / 2.f);
}

void Editor_State::initModes()
{
	editor_modes.push_back(new DefaultMode{ State_Data, map,&EditorStatedata });
}

Editor_State::Editor_State(StateData* State_Data) : State{ State_Data }
{
	initVariables();
	initEditorStateData();
	initKeybinds();
	initFonts();
	initButtons();
	initPauseMenu();
	initTileMap();
	initView();
	initGUI();
	initModes();

}

Editor_State::~Editor_State()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}
	delete pmenu;
	delete map;
	
	for (size_t i = 0; i < editor_modes.size(); i++) {
		delete editor_modes.at(i);
	}
	
	
}

void Editor_State::update(const float& dt)
{
	updateMousePositions(&MainView);
	updateInput(dt);
	updateKeyTime(dt);
	if (!paused) {//unpaused
		updateButtons();
		updateGUI(dt);
		updateEditorInput(dt);
		updateModes(dt);
	}
	else {
		pmenu->update(mousePosWindow);
		updatePauseMenuButtons();
	}
}

void Editor_State::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->setView(MainView);
	map->render(*target, mousePosGrid, true);
	map->DeferredRender(*target);
	target->setView(window->getDefaultView());
	renderButtons(target);

	renderGUI(*target);
	renderModes(*target);
	if (paused) { //paused menu rendering
		target->setView(window->getDefaultView());
		pmenu->render(*target);
	}
}



void Editor_State::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeyTime()) {
		if (!paused) {
			pauseState();
		}
		else {
			unpauseState();
		}
	}
}

void Editor_State::updatePauseMenuButtons()
{
	if (pmenu->isPressed("QUIT")) {
		endState();
	}
	if (pmenu->isPressed("SAVE")) {
		map->saveToFile("text.txt");
	}
	if (pmenu->isPressed("LOAD")) {
		map->loadFromFile("text.txt");
	}
}

void Editor_State::updateModes(const float& dt)
{
	editor_modes[DEFAULT_MODE]->update(dt);
}

void Editor_State::renderModes(sf::RenderTarget& target)
{
	editor_modes[DEFAULT_MODE]->render(target);
}

void Editor_State::updateButtons()
{
	for (auto& it : buttons) {
		it.second->update(mousePosWindow);
	}
}

void Editor_State::updateGUI(const float& dt)
{
	
}

void Editor_State::renderButtons(sf::RenderTarget* target)
{

	for (auto but : buttons) {
		but.second->render(target);
	}
}

void Editor_State::renderGUI(sf::RenderTarget& target)
{

}
