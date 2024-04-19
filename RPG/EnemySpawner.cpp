#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, short type,
	sf::Vector2i grid_position, float grid_Size, int enemy_type, int enemy_count, int enemy_spawn_timer, int enemy_max_Distance):Tile(grid_x,grid_y,gridSizeF,texture,texture_rect,false,TileTypes::ENEMYSPAWNER)
{
	gridPosition = grid_position;
	Enemytype = enemy_type;
	EnemyCount = enemy_count;
	EnemySpawnTimer = enemy_spawn_timer;
	EnemymaxDistance = enemy_max_Distance;
	shape.setSize(sf::Vector2f{ grid_Size, grid_Size });
	shape.setFillColor(sf::Color::Blue);

}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update()
{
}


void EnemySpawner::render(sf::RenderTarget& target, sf::Vector2f player_Pos, sf::Shader* shader) const
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


