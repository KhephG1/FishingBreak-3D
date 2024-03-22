#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
class GameState: public State
{
private:
	//functions
	void initTextures();
	void initKeybinds();
	void initPlayers();
	void initTileMap();
	Player* player;
	PauseMenu* pmenu;
	sf::Font fnt;
	TileMap* tMap;
public:

	GameState(StateData* state_data);
	virtual ~GameState();
	void initFonts();
	void initPauseMenu();
	void updatePauseButtons();
	virtual void updateInput(const float& dt) override;
	virtual void update (const float& dt) override;
	virtual void render (sf::RenderTarget* target = nullptr) override;
	virtual void updatePlayerInput(const float& dt);
};
#endif
