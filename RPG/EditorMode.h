
#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "State.h"
#include "TileMap.h"
#include "GUI.h"
class State;
class StateData;
class EditorStateData {
public:
	EditorStateData() {};
	//Variables
	sf::View* view;
	sf::Vector2i* mousePosScreen;
	sf::Vector2i* mousePosWindow;
	sf::Vector2f* mousePosView;
	sf::Vector2i* mousePosGrid;
	sf::Font* font;
	float* keyTime;
	float* keyTimeMax;
	//pointer to the keybinds map in states.h
	std::map<std::string, int>* keybinds;

};
class EditorMode
{
protected:
	StateData* stateData;
	TileMap* tMap;
	EditorStateData editorStateData;
public:
	EditorMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data);
	virtual~EditorMode();
	//
	const  bool getKeyTime();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void updateInput(const float& dt) = 0;

	virtual void updateGUI(const float& dt) = 0;

	virtual void renderGUI(sf::RenderTarget& target) = 0;

};

#endif