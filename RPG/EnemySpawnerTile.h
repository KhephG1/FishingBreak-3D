#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H
#include "Enemy.h"
#include "Tile.h"
// a tile we can place that will spawn and manage enemies. when out of view it will ensure all enemies associated with the tile despawn
class EnemySpawnerTile:public Tile
{
private:
	bool spawned;
	sf::Vector2i gridPosition;
	int Enemytype;
	int EnemyCount;
	int EnemyCounter;
	sf::Clock EnemySpawnTimer;
	sf::Int32 EnemyTimeToSpawn;
	float EnemymaxDistance;
	sf::RectangleShape shape;
public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, 
		int enemy_type, int enemy_count,int enemy_time_to_spawn,int enemy_max_Distance );
	virtual ~EnemySpawnerTile();
	void update() override;
	void render(sf::RenderTarget& target, sf::Vector2f player_Pos = sf::Vector2f{}, sf::Shader* shader = nullptr) const;
	virtual const std::string getAsString() const;
	void SetSpawned(const bool spawned);
	const bool canSpawn() const;
	void decreaseEnemyCounter();
	void increaseEnemyCounter();
	//ACCESSORS
	const bool& getSpawned() const;
	const int& getEnemyCounter() const;
	const int& getEnemyAmount() const;
};


#endif