#ifndef GAME_H
#define GAME_H
#include "MainMenuState.h"
class Game
{
private:
	//Variables
	float gridSize = 64.f;
	sf::RenderWindow* window{};
	sf::Event event{};
	float dt{};
	GraphicSettings gfxSettings;
	StateData stateData;
	//tracks time for one update and one render (a frame)
	//allows us to move in a frame independent way
	sf::Clock dtClock{};
	std::stack<State*> states;

	std::map<std::string, int> supportedKeys{};
	//Initialization
	void initWindow();
	void initStates();
	void initKeys();
	void initStateData();
	void initGraphicSettings();
	//we cant create objects of state only pointers and references
public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//Functions
	void updateSFMLEvents();
	void update();
	void render();
	void run();
	void updateDt();
	
};

#endif