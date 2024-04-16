#include "stdafx.h"
#include "Editor_State.h"

void Editor_State::initVariables()
{
	textureRect = sf::IntRect{ 0,0,(int)State_Data->gridsize, (int)State_Data->gridsize };
	collision = false;
	type = DEFAULT;
	camera_speed = 100.f;
}

void Editor_State::initBackgrounds()
{
	
}
void Editor_State::initPauseMenu()
{
	sf::VideoMode& vm = State_Data->gfxSettings->resolution;
	pmenu = new PauseMenu{vm, font };
	pmenu->addButton("QUIT", "QUIT", p2pY(0.46f,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));
	pmenu->addButton("SAVE", "SAVE", p2pY(0.65,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));
	pmenu->addButton("LOAD", "LOAD", p2pY(0.556,vm), p2pX(0.0781f, vm), p2pY(0.042f, vm));

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

void Editor_State::initText()
{
	cursorText.setPosition(mousePosView.x, mousePosView.y - 50.f);
	cursorText.setFont(font);
	cursorText.setCharacterSize(12);
	cursorText.setString(std::to_string(mousePosView.x) + "," + std::to_string(mousePosView.y) + " " + std::to_string(textureRect.left));
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& getKeyTime()) {
		if (buttons["HIDE"]->isPressed()) {
			texSelector->gethidden() = !texSelector->gethidden();
		}
		if (texSelector->getActive()) {
			textureRect = texSelector->getTextureRect();
		}
		else {
			if (!sidebar.getGlobalBounds().contains(sf::Vector2f{ mousePosWindow })) {
				map->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, type);
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime()) {
		if(!texSelector->getActive()&& !sidebar.getGlobalBounds().contains(sf::Vector2f{ mousePosWindow })){
			map->removeTile(mousePosGrid.x, mousePosGrid.y,0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION"))) && getKeyTime()) {
		collision = !collision;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TYPE_INC"))) && getKeyTime()) {
		//increase if less than max type number
		type++;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TYPE_DEC"))) && getKeyTime()) {
		if (type > 0) {
			type--;
		}
	}
	

}

void Editor_State::initGUI()
{
	selectorRect.setSize(sf::Vector2f{ State_Data->gridsize, State_Data->gridsize });
	selectorRect.setFillColor(sf::Color(255,255,255,150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
	selectorRect.setTexture(map->getileSheet());
	selectorRect.setTextureRect(textureRect);
	texSelector = new GUI::textureSelector{0,0,800.f,500.f,State_Data->gridsize, map->getileSheet(), font};
	sidebar.setSize(sf::Vector2f{ (float)State_Data->gfxSettings->resolution.width,80.f });
	sidebar.setPosition(0, State_Data->gfxSettings->resolution.height - sidebar.getSize().y);
	sidebar.setFillColor(sf::Color{ 50,50,50,100 });
	sidebar.setOutlineThickness(1.f);
}

void Editor_State::initView()
{
	MainView.setSize(sf::Vector2f{ (float)State_Data->gfxSettings->resolution.width, (float)State_Data->gfxSettings->resolution.height });
	MainView.setCenter(State_Data->gfxSettings->resolution.width / 2.f, State_Data->gfxSettings->resolution.height / 2.f);
}

Editor_State::Editor_State(StateData* State_Data) : State{ State_Data }
{
	initVariables();
	initBackgrounds();
	initKeybinds();
	initFonts();
	initText();
	initButtons();
	initPauseMenu();
	initTileMap();
	initView();
	initGUI();

}

Editor_State::~Editor_State()
{
	for (auto iter = buttons.begin(); iter != buttons.end(); ++iter) {
		delete iter->second;
	}
	delete pmenu;
	delete map;
	delete texSelector;
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
	target->draw(background);
	target->setView(MainView);
	map->render(*target, mousePosGrid, true);
	map->DeferredRender(*target);
	target->setView(window->getDefaultView());
	renderButtons(target);

	renderGUI(*target);

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

void Editor_State::updateButtons()
{
	for (auto& it : buttons) {
		it.second->update(mousePosWindow);
	}
}

void Editor_State::updateGUI(const float& dt)
{
	if (!texSelector->getActive()) {
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(mousePosGrid.x * State_Data->gridsize, mousePosGrid.y * State_Data->gridsize);
	}
	cursorText.setPosition(mousePosView.x + 100.f, mousePosView.y - 50.f);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << "\n " << mousePosGrid.x << mousePosGrid.y
		<< "\n" << textureRect.left << " "
		<< textureRect.top << "\n" << "Collision: " << collision
		<< "\n" << "Type: " << type
		<< "\n" << "Tiles: " << map->getLayer(mousePosGrid.x, mousePosGrid.y, layer);
	cursorText.setString(ss.str());
	
	

	texSelector->update(sf::Vector2i{(int)mousePosWindow.x, (int)mousePosWindow.y}, dt);
}

void Editor_State::renderButtons(sf::RenderTarget* target)
{

	for (auto but : buttons) {
		but.second->render(target);
	}
}

void Editor_State::renderGUI(sf::RenderTarget& target)
{
	if (!texSelector->getActive()) {
		target.setView(MainView);
		target.draw(selectorRect);
	}
	target.setView(window->getDefaultView());
	texSelector->render(target);
	target.draw(sidebar);
	target.setView(MainView);
	target.draw(cursorText);
}
