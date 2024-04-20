

#ifndef DEFAULTMODE_H
#define DEFAULTMODE_H

#include "EditorMode.h"

class DefaultMode :
	public EditorMode
{
private:
	int layer;
	sf::Text cursorText;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	GUI::textureSelector* texSelector;
	bool collision;
	std::string tileAddLock;
	short type;

	sf::RectangleShape sidebar;
public:
	DefaultMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data);
	virtual ~DefaultMode();
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
	virtual void updateInput(const float& dt);

	virtual void updateGUI(const float& dt);

	virtual void renderGUI(sf::RenderTarget& target);
	void initVariables();
	void initGUI();
};

#endif