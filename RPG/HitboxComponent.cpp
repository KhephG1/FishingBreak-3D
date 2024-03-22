#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprt, float offset_x, float offset_y, float width, float height) : sprite{sprt}, offsetX{offset_x}, offsetY{offset_y}
{
	hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);

	hitbox.setSize(sf::Vector2f{ width, height });

	hitbox.setFillColor(sf::Color::Transparent);

	hitbox.setOutlineColor(sf::Color::Green);

	hitbox.setOutlineThickness(3.f);

}
HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& rect)
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
