#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	movementComp = nullptr;
	sprite = nullptr;
	texture = nullptr;
	skillComponent = nullptr;
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
	delete attributeComponent;
	delete skillComponent;
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

void Entity::createAttributeComponent(const int lvl)
{
	attributeComponent = new AttributeComponent{lvl};
}

void Entity::createSprite(sf::Texture* tex)
{
	texture = tex;
	sprite = new sf::Sprite{ *tex };

}

void Entity::createSkillComponent()
{
	skillComponent = new SkillComponent{};
}

void Entity::createAIComponent()
{
}

const sf::Vector2f Entity::getPosition() const
{
	if (hitbox)
		return hitbox->getPosition();
	
	return sprite->getPosition();
	
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitbox) {
		return hitbox->getGlobalBounds();
	}
	return sprite->getGlobalBounds();
}

const sf::Vector2i Entity::getGridPosition(const int GridSizeI) const
{
	if (hitbox)
		return sf::Vector2i{ static_cast<int>(hitbox->getPosition().x) / GridSizeI, static_cast<int>(hitbox->getPosition().y) / GridSizeI };

	return sf::Vector2i{ static_cast<int>(sprite->getPosition().x) / GridSizeI, static_cast<int>(sprite->getPosition().y) / GridSizeI };
}

const sf::FloatRect& Entity::getNextBounds(const float& dt) const
{
	if (hitbox && movementComp) {
		return hitbox->getNextPosition(movementComp->getVelocity() * dt);
	}
	throw std::runtime_error{ "ENTITY::GETNEXTBOUNDS ERROR" };
}

const sf::Vector2f Entity::getCenter() const
{
	if (hitbox) {
		sf::Vector2f temp{ hitbox->getPosition().x + hitbox->getGlobalBounds().width / 2.f, hitbox->getPosition().y + hitbox->getGlobalBounds().height / 2.f };
		return temp;
	}

	return sf::Vector2f{ sprite->getPosition().x + sprite->getGlobalBounds().width / 2.f, sprite->getPosition().y + sprite->getGlobalBounds().height / 2.f };
}

//the entity set position function handles setting the hitbox position (if it has one) and the sprite position only otherwise
//the hotbox set position handles setting the sprite position relative to the hitbox position
void Entity::setPosition(const float x, const float y)
{
	if (hitbox) {
		hitbox->setPosition(x, y);
	}else if (sprite) {
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
	if (skillComponent) {
		skillComponent->gainExp(ENDURANCE, 1);
		
	}
}


void Entity::stopVelocity()
{
	movementComp->stopVelocity();
}

void Entity::stopVelocityX()
{
	movementComp->stopVelocityX();
}

void Entity::stopVelocityY()
{
	movementComp->stopVelocityY();
}

const float Entity::getDistance(Entity* other) const
{
	sf::Vector2f temp = other->getCenter() - getCenter();
	float tempmagnitude = std::sqrt(temp.x * temp.x + temp.y * temp.y);
	return tempmagnitude;
}


