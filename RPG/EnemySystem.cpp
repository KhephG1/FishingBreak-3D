#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& active_Enemies,std::map<std::string, sf::Texture>& texture_map): activeEnemies{ active_Enemies }, textures{ texture_map }
{
	
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		activeEnemies.push_back(new Rat(xPos, yPos, &textures["RAT1_SHEET"]));
		break;
	default:
		std::cout << "createEnemy::ERROR CREATING ENEMY " << std::endl;
		break;
	}
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget& target)
{
}
