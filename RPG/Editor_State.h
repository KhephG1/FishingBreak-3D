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
	sf::Font font;
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	PauseMenu* pmenu;
	TileMap* map;
	sf::Text cursorText;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	GUI::textureSelector* texSelector;
	Button* gamestate_btn;

	//functions
	void initPauseMenu();
	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initText();
	void initButtons();
	void initTileMap();
	void updateEditorInput();
	void initGUI();
public:

	Editor_State(StateData* State_Data);
	virtual ~Editor_State();
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updateInput(const float& dt) override;
	void updatePauseMenuButtons();
	void updateButtons();
	void updateGUI();
	void renderButtons(sf::RenderTarget* Target);
	void renderGUI(sf::RenderTarget& target);
};
#endif
