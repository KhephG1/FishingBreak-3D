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

Tile::Tile(int grid_x, int grid_y,float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, bool collide, short the_type) {
	
	shape.setPosition(grid_x * gridSizeF, grid_y * gridSizeF);
	shape.setTexture(texture);
	shape.setTextureRect(texture_rect);
	collision = collide;
	type = the_type;
}

void Tile::render(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Shader* shader) const
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);
		target.draw(shape, shader);
	}
	else {
		target.draw(shape);
	}
}

void Tile::update()
{
	shape.setColor(sf::Color::Blue);
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
//overload the stream insertion operator to easily send the tile to a file
std::ostream& operator<<(std::ostream& stream, Tile tile) {
	stream << tile.shape.getTextureRect().left << " " << tile.shape.getTextureRect().top << " " << tile.collision << " " << tile.type;
	return stream;
}

