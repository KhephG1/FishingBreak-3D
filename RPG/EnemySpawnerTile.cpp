#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect,
	int enemy_type, int enemy_count, int enemy_spawn_timer, int enemy_max_Distance):Tile(TileTypes::ENEMYSPAWNER,grid_x,grid_y,gridSizeF,texture,texture_rect,false)
{
	spawned = false;
	Enemytype = enemy_type;
	EnemyCount = enemy_count;
	EnemySpawnTimer = enemy_spawn_timer;
	EnemymaxDistance = enemy_max_Distance;
	

}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

void EnemySpawnerTile::update()
{
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
		<< Enemytype << " " << EnemyCount << " " << EnemySpawnTimer << " " << EnemymaxDistance;

	//
	//  << ss.str() << "\n";

	return ss.str();
}

void EnemySpawnerTile::SetSpawned(const bool spawned)
{
	this->spawned = spawned;
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return spawned;
}

