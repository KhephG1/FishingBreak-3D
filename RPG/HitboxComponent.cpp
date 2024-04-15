#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprt, float offset_x, float offset_y, float width, float height) : sprite{sprt}, offsetX{offset_x}, offsetY{offset_y}
{
	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);

	hitbox.setSize(sf::Vector2f{ width, height });

	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setOutlineColor(sf::Color::Green);
	//note to future self, always use negative outline thicknesses since it messes with collision detection
	hitbox.setOutlineThickness(-1.f);
	nextPosition.left = 0.f;
	nextPosition.top = 0.f;
	nextPosition.width = width;
	nextPosition.height = height;

}
HitboxComponent::~HitboxComponent()
{
}

const sf::Vector2f HitboxComponent::getPosition() const
{
	return hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	//velocity already multiplied by delta time
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;
	return nextPosition;
}
//the hitbox setposition sets the position of the rectangle used for collision and the sprite's position relative to this rectangle
void HitboxComponent::setPosition(const sf::Vector2f position)
{
	hitbox.setPosition(position);
	//set the sprites position to the same position as the hitbox offset by a preset amount (so the hitbox only surrounds the part of the sprite we want)
	sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	hitbox.setPosition(x,y);
	sprite.setPosition(x - offsetX, y - offsetY);
}

bool HitboxComponent::intersects(const sf::FloatRect& rect)
{
	return hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}
