#include "stdafx.h"
#include "Tile.h"

Tile::~Tile()
{
}

Tile::Tile()
{
	type = DEFAULT;
	collision = false;

}

Tile::Tile(short the_type,int grid_x, int grid_y,float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, const bool collision) {
	
	shape.setPosition(grid_x * gridSizeF, grid_y * gridSizeF);
	shape.setTexture(texture);
	shape.setTextureRect(texture_rect);
	this->collision = collision;
	type = the_type;
}

const sf::Vector2f& Tile::getPosition() const
{
	return shape.getPosition();
}
const bool& Tile::getCollision() const
{
	
	return collision;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds);
}
const sf::FloatRect Tile::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}
const short& Tile::getType() const
{
	return type;
}


