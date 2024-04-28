#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H
#include "EnemySpawnerTile.h"
#include "Rat.h"
enum EnemyTypes {RAT = 0};
class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies,std::map<std::string, sf::Texture>& texture_map, Entity& plr);
	virtual ~EnemySystem();

	//Accessors
	//Modifiers


	//Functions
	void createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& spawnerTile);
	void removeEnemy(const int index);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif ENEMYSYSTEM_H