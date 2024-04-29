#pragma once
#pragma once

#include "Enemy.h"

class Bird1 :
	public Enemy
{
private:
	void initVariables();
	void initAnimations();
	void initAI();
	void initGUI();

	sf::RectangleShape hpBar;

	AIFollow* follow;

public:
	Bird1(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
	virtual ~Bird1();

	//Functions
	void updateAnimation(const float& dt);
	virtual void update(const float& dt, sf::Vector2f mouse_pos_view) override;

	void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position) override;
};
