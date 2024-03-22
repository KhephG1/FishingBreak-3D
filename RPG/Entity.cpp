#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	movementComp = nullptr;
	sprite = nullptr;
	texture = nullptr;
}

Entity::Entity()
{
	initVariables();

}

Entity::~Entity()
{
	delete sprite;
	delete movementComp;
	delete animationComponent;
	delete hitbox;
}

void Entity::createMovementComponent(const float maxSpeed, const float accel, const float decel)
{
	movementComp = new MovementComponent{ *sprite, maxSpeed, accel, decel };
}

void Entity::createAnimationtComponent(sf::Texture& texture_sheet)
{
	animationComponent = new AnimationComponent{ *sprite,texture_sheet };
}

void Entity::createHitboxComponent(sf::Sprite& sprt, float offset_x, float offset_y, float width, float height)
{
	hitbox = new HitboxComponent(sprt, offset_x, offset_y, width, height);
}

void Entity::createSprite(sf::Texture* tex)
{
	texture = tex;
	sprite = new sf::Sprite{ *tex };

}

void Entity::setPosition(const float x, const float y)
{
	if (sprite) {
		sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dt,const float dir_x, const float dir_y)
{
	if (sprite && movementComp) {
		movementComp->move(dir_x, dir_y, dt); //sets velocity
		sprite->move(movementComp->getVelocity() * dt); //uses velocity
	}
	else {
		std::cout << "error" << std::endl;
	}
}

void Entity::update(const float& dt)
{
	if (movementComp) {
		movementComp->update(dt);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (sprite) {
		target->draw(*sprite);
	}

	if (hitbox) {
		hitbox->render(*target);
	}
}


