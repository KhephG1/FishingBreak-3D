#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& active_Enemies,std::map<std::string, sf::Texture>& texture_map, Entity& plr): activeEnemies{ active_Enemies }, textures{ texture_map }, player{plr}
{
	
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos, EnemySpawnerTile& spawnerTile)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		activeEnemies.push_back(new Rat(xPos, yPos, &textures["RAT1_SHEET"], spawnerTile,player));
		spawnerTile.increaseEnemyCounter();
		break;
	case EnemyTypes::BIRD:
		this->activeEnemies.push_back(new Bird1(xPos, yPos, this->textures["BIRD1_SHEET"], spawnerTile, this->player));
		spawnerTile.increaseEnemyCounter();
		break;
	default:
		std::cout << "createEnemy::ERROR CREATING ENEMY " << std::endl;
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	activeEnemies.at(index)->getSpawnerTile().decreaseEnemyCounter();
	delete activeEnemies.at(index);
	activeEnemies.erase(activeEnemies.begin() + index);

}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget& target)
{
}
