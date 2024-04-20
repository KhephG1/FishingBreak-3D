#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "DefaultMode.h"

enum EditorModes {DEFAULT_MODE = 0, ENEMY};

using namespace GUI;
class Editor_State: public State
{
private:
	sf::View MainView;
	float camera_speed;
	sf::Font font;
	std::map<std::string, Button*> buttons;
	PauseMenu* pmenu;
	TileMap* map;
	EditorStateData EditorStatedata;
	
	std::vector<EditorMode*> editor_modes;

	//functions
	void initPauseMenu();
	void initVariables();
	void initEditorStateData();
	void initKeybinds();
	void initFonts();
	void initButtons();
	void initTileMap();
	void updateEditorInput(const float& dt);
	void initGUI();
	void initView();
	void initModes();
public:

	Editor_State(StateData* State_Data);
	virtual ~Editor_State();
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updateInput(const float& dt) override;
	void updatePauseMenuButtons();
	void updateModes(const float& dt);
	void renderModes(sf::RenderTarget& target);
	void updateButtons();
	void updateGUI(const float& dt);
	void renderButtons(sf::RenderTarget* Target);
	void renderGUI(sf::RenderTarget& target);
};
#endif
