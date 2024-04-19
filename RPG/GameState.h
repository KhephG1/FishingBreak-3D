#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"
#include "Enemy.h"
class GameState: public State
{
private:
	//functions
	void initDifferedRender();
	void initView();
	void initTextures();
	void initKeybinds();
	void initPlayers();
	void initTileMap();
	sf::View MainView;
	sf::Vector2i ViewGridPosition;
	//these variables will be used for rendering the map without tearing
	sf::RenderTexture render_tex;
	sf::Sprite renderSprite;
	Player* player;

	PauseMenu* pmenu;
	sf::Font fnt;
	TileMap* tMap;
	PlayerGUI* playerGUI;
	sf::Shader core_shader;
public:

	GameState(StateData* state_data);
	virtual ~GameState();
	void initFonts();
	void initPauseMenu();
	void initPlayerGUI();
	void initShaders();
	void updateTileMap(const float& dt);
	void updatePauseButtons();
	void updateView(const float& dt);
	void updatePlayerGUI(const float& dt);
	virtual void updateInput(const float& dt) override;
	virtual void update (const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;
	virtual void updatePlayerInput(const float& dt);
};
#endif
