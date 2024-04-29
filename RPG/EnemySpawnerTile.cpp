#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect,
	int enemy_type, int enemy_count, sf::Int32 enemy_time_to_spawn, int enemy_max_Distance):Tile(TileTypes::ENEMYSPAWNER,grid_x,grid_y,gridSizeF,texture,texture_rect,false)
{
	spawned = false;
	Enemytype = enemy_type;
	EnemyCount = enemy_count;
	EnemyCounter = 0;
	EnemySpawnTimer.restart();
	EnemyTimeToSpawn = enemy_time_to_spawn;
	EnemymaxDistance = enemy_max_Distance;
	

}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

void EnemySpawnerTile::update()
{
	if (canSpawn()) {
		spawned = false;
	}
}


void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Vector2f player_Pos, sf::Shader* shader) const
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", player_Pos);
		target.draw(shape, shader);
	}
	else {
		target.draw(shape);
	}
}


const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	/*
	x, y, z (done in tilemap save)
	type,
	rect x, rect y,
	enemy type,
	enemy amount
	enemy time to spawn
	enemy max distance
	*/

	ss << type << " " << shape.getTextureRect().left << " " << shape.getTextureRect().top << " "
		<< Enemytype << " " << EnemyCount << " " << EnemyTimeToSpawn << " " << EnemymaxDistance;

	//
	//  << ss.str() << "\n";

	return ss.str();
}

void EnemySpawnerTile::SetSpawned(const bool spawned)
{
	this->spawned = spawned;
	EnemySpawnTimer.restart();
}

const bool EnemySpawnerTile::canSpawn() const
{
	if(EnemySpawnTimer.getElapsedTime().asMilliseconds() >= EnemyTimeToSpawn*50)
		return true;

	return false;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (EnemyCounter < 0) {
		EnemyCounter = 0;
	}
	else {
		--EnemyCounter;
	}
}

void EnemySpawnerTile::increaseEnemyCounter()
{
	if (EnemyCounter > EnemyCount) {
		EnemyCounter = EnemyCount;
	}
	else {
		++EnemyCounter;
	}
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return spawned;
}

const int& EnemySpawnerTile::getEnemyCounter() const
{
	return EnemyCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return EnemyCount;
}

