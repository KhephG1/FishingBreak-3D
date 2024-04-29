#ifndef STATE_H
#define STATE_H
#include "Entity.h"
#include "Player.h"
#include "GraphicsSettings.h"

class State;

class StateData {
public:
	StateData();
	//Variables
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	GraphicSettings* gfxSettings;
	float gridsize;
	float endGame{ false };
};
class State
{
private:
protected:
	//a pointer to a stack of state pointers (will point it to the one in the game class)
	std::stack<State*>* states;
	StateData* State_Data;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	float gridSize;
	bool quit;
	bool paused;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;
	float keyTime;
	float keyTimeMax;
	//Resources
	std::map<std::string,sf::Texture> textures;

	//functions
	virtual void initKeybinds() = 0;
public:
	const bool& getQuit() const;
	const  bool getKeyTime();
	State(StateData* state_Data);
	virtual ~State();
	void endState();
	void pauseState();
	void unpauseState();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePositions(sf::View* view);
	virtual void updateKeyTime(const float dt);



	
};
#endif
