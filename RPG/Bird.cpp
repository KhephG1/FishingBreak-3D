#include "stdafx.h"
#include "Bird.h"

//Initializer functions
void Bird1::initVariables()
{

}

void Bird1::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 0, 2, 0, 61, 57);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 1, 2, 1, 61, 57);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 2, 2, 2, 61, 57);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 3, 2, 3, 61, 57);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 61, 57);
}

void Bird1::initAI()
{

}

void Bird1::initGUI()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(60.f, 10.f));
	this->hpBar.setPosition(this->sprite->getPosition());
}

//Constructors / Destructors
Bird1::Bird1(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	createSprite(&texture_sheet);
	this->initVariables();
	this->initGUI();
	this->createHitboxComponent(*this->sprite, 15.f, 15.f, 30.f, 30.f);
	this->createMovementComponent(70.f, 350.f, 50.f);
	this->createAnimationtComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimations();

	this->follow = new AIFollow(*this, player);
}


Bird1::~Bird1()
{
	delete this->follow;
}

void Bird1::updateAnimation(const float& dt)
{
	if (this->movementComp->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComp->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComp->getVelocity().x, this->movementComp->getMaxVelocity());
	}
	else if (this->movementComp->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComp->getVelocity().x, this->movementComp->getMaxVelocity());
	}
	else if (this->movementComp->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComp->getVelocity().y, this->movementComp->getMaxVelocity());
	}
	else if (this->movementComp->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComp->getVelocity().y, this->movementComp->getMaxVelocity());
	}

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite->setColor(sf::Color::Red);
	}
	else
		this->sprite->setColor(sf::Color::White);
}

void Bird1::update(const float& dt, sf::Vector2f mouse_pos_view)
{
	Enemy::update(dt, mouse_pos_view);

	this->movementComp->update(dt);

	//Update GUI REMOVE THIS!!!!
	this->hpBar.setSize(sf::Vector2f(60.f * (static_cast<float>(this->attributeComponent->hp) / this->attributeComponent->hpMax), 10.f));
	this->hpBar.setPosition(this->sprite->getPosition());

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitbox->update();

	this->follow->update(dt);
}

void Bird1::render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target->draw(*this->sprite,shader);
	}
	else
	{
		target->draw(*this->sprite);
	}

	target->draw(this->hpBar);

	if (show_hitbox)
		this->hitbox->render(*target);
}