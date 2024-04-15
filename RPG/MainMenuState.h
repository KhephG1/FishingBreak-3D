#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "GameState.h"
#include "Editor_State.h"
#include "GUI.h"
#include "SettingState.h"

using namespace GUI;
class MainMenuState: public State
{
private:
	sf::RectangleShape background;
	sf::Font font;
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;

	Button* gamestate_btn;

	//functions
	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initGUI();
public:

	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updateInput(const float& dt) override;
	void updateButtons();
	void renderButtons(sf::RenderTarget* Target);
	void resetGUI();
};
#endif
