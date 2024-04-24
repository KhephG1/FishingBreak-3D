
#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H
#include "EditorMode.h"
#include "EnemySpawnerTile.h"
class EnemyEditorMode :
    public EditorMode
{
private:
	sf::Text cursorText;
	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	sf::IntRect textureRect;
	void initVariables();
	void initGUI();
	int type;
	int amount;
	int TimeToSpawn;
	int maxDistance;
public:
	EnemyEditorMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data);
	virtual ~EnemyEditorMode();
	//functions

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
	virtual void updateInput(const float& dt);

	virtual void updateGUI(const float& dt);

	virtual void renderGUI(sf::RenderTarget& target);

};

#endif