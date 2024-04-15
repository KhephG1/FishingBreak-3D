#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H
#include "State.h"
#include "GUI.h"
#include "GraphicsSettings.h"
using namespace GUI;
class SettingState :
    public State
{
private:
	
	sf::RectangleShape background;
	sf::Font font;
	sf::Texture backgroundTexture;
	std::map<std::string, Button*> buttons;
	std::map<std::string, GUI::DropDownList*> dropdownL;

	sf::Text optionsText;
	std::vector<sf::VideoMode> modes;
	Button* gamestate_btn;
	
	//functions
	void initVariables();
	void initBackgrounds();
	void initKeybinds();
	void initFonts();
	void initGUI();
public:
    SettingState(StateData* state_data);
    virtual ~SettingState();
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updateInput(const float& dt) override;
	void updateGUI(const float& dt);
	void renderGUI(sf::RenderTarget* Target);
};

#endif