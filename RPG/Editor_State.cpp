#include "stdafx.h"
#include "Editor_State.h"

void Editor_State::initVariables()
{
	textureRect = sf::IntRect{ 0,0,(int)State_Data->gridsize, (int)State_Data->gridsize };
}

void Editor_State::initBackgrounds()
{
	
}
void Editor_State::initPauseMenu()
{
	pmenu = new PauseMenu{ *window, font };
	pmenu->addButton("QUIT", "QUIT", 500.f);
}

void Editor_State::initKeybinds()
{
	std::ifstream stream("Config/editor_state_keybinds.txt", std::ios::in);
	if (!stream.is_open()) {
		throw std::runtime_error{ "error" };
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
	
}

void Editor_State::initTileMap()
{
	map = new TileMap{ State_Data->gridsize, 10,10 };
}

void Editor_State::updateEditorInput()
{
	//Adding tiles to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& getKeyTime()) {
		map->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime()) {
		map->removeTile(mousePosGrid.x, mousePosGrid.y,0);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getKeyTime()) {
		if (textureRect.left < 100) {
			textureRect.left += 100;
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
	texSelector = new GUI::textureSelector{ 20.f,20.f,500.f,500.f,State_Data->gridsize, map->getileSheet() };
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
	updateMousePositions();
	updateInput(dt);
	updateKeyTime(dt);
	if (!paused) {//unpaused
		updateButtons();
		updateGUI();
		updateEditorInput();
	}
	else {
		pmenu->update(mousePosView);
		updatePauseMenuButtons();
	}
	std::cout << mousePosView.x << " " << mousePosView.y << std::endl;
}

void Editor_State::render(sf::RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	target->draw(background);

	map->render(*target);
	renderButtons(target);
	renderGUI(*target);
	

	if (paused) { //paused menu rendering
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
}

void Editor_State::updateButtons()
{
	for (auto& it : buttons) {
		it.second->update(mousePosView);
	}
}

void Editor_State::updateGUI()
{
	selectorRect.setTextureRect(textureRect);
	selectorRect.setPosition(mousePosGrid.x * State_Data->gridsize, mousePosGrid.y * State_Data->gridsize);
	cursorText.setPosition(mousePosView.x + 100.f, mousePosView.y - 50.f);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << "\n " << mousePosGrid.x << mousePosGrid.y << "\n" << textureRect.left << " " << textureRect.top;
	cursorText.setString(ss.str());

	texSelector->update(mousePosWindow);
}

void Editor_State::renderButtons(sf::RenderTarget* target)
{

	for (auto but : buttons) {
		but.second->render(target);
	}
}

void Editor_State::renderGUI(sf::RenderTarget& target)
{
	target.draw(selectorRect);
	target.draw(cursorText);
	texSelector->render(target);
}
