#include "stdafx.h"
#include "Game.h"
//Static functions'


void Game::initStateData()
{
	stateData.window = window;
	stateData.gfxSettings = &gfxSettings;
	stateData.supportedKeys = &supportedKeys;
	stateData.states = &states;
	stateData.gridsize = gridSize;
}

//initializer functions
void Game::initWindow()
{
	if (gfxSettings.fullscreen) {
		window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::Style::Fullscreen, gfxSettings.contextset);
	}
	else {
		window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, gfxSettings.contextset);
	}
	window->setFramerateLimit(gfxSettings.frameRateLim);
}
void Game::initStates()
{
	states.push(new MainMenuState(&stateData));
}
void Game::initKeys()
{
	
	supportedKeys["ESCAPE"] = sf::Keyboard::Key::Escape;
	supportedKeys["A"] = sf::Keyboard::Key::A;
	supportedKeys["D"] =  sf::Keyboard::Key::D;
	supportedKeys["W"] = sf::Keyboard::Key::W;
	supportedKeys["S"] = sf::Keyboard::Key::S;
	supportedKeys["C"] = sf::Keyboard::Key::C;
	supportedKeys["UP"] = sf::Keyboard::Key::Up;
	supportedKeys["DOWN"] = sf::Keyboard::Key::Down;
	supportedKeys["L"] = sf::Keyboard::Key::L;
	


}
void Game::initGraphicSettings()
{
	gfxSettings.loadFromFile("Config/graphics.txt");
	
}
//constructor /destructors
Game::Game() {
	initWindow();
	initKeys();
	initStateData();
	initStates();
}

Game::~Game()
{
	delete window;
	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
}
//functions
void Game::updateSFMLEvents()
{
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
	}
}

void Game::update()
{
	updateSFMLEvents();
	//the has focus function returns true if the current instance of the window is the one taking input such as keystrokes and mouse movements and false otherwise
	if (!states.empty()) {
		states.top()->update(dt);
		if (window->hasFocus()) {
			if (states.top()->getQuit()) {
				states.top()->endState();
				delete states.top();
				states.pop();
			}
		}
	}
	//Application end
	else {
		//closing window closes application since while loop in run depends on window being open
		window->close();
	}
}

void Game::render()
{
	window->clear();

	if (!states.empty()) {
		states.top()->render();
	}
	window->display();
}

void Game::run()
{
	while (window->isOpen()) {
		updateDt();
		update();
		render();

	}
}

void Game::updateDt()
{
	//update the dt variable with the time taken to update and render a frame
	dt = dtClock.restart().asSeconds();

	//system("cls");
	//std::cout << dt<<"\n";
}
