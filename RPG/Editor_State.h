#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"
using namespace GUI;
class Editor_State: public State
{
private:
	sf::RectangleShape background;
	sf::RectangleShape sidebar;
	sf::Font font;
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	PauseMenu* pmenu;
	TileMap* map;
	sf::Text cursorText;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	GUI::textureSelector* texSelector;
	bool collision;
	std::string tileAddLock;
	short type;
	sf::View MainView;
	float camera_speed;
	//current layer we are working on in the editor
	int layer;
	

	//functions
	void initPauseMenu();
	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initText();
	void initButtons();
	void initTileMap();
	void updateEditorInput(const float& dt);
	void initGUI();
	void initView();
public:

	Editor_State(StateData* State_Data);
	virtual ~Editor_State();
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updateInput(const float& dt) override;
	void updatePauseMenuButtons();
	void updateButtons();
	void updateGUI(const float& dt);
	void renderButtons(sf::RenderTarget* Target);
	void renderGUI(sf::RenderTarget& target);
};
#endif
