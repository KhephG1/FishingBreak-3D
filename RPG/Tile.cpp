#include "stdafx.h"
#include "Tile.h"

Tile::~Tile()
{
}

Tile::Tile()
{

}

Tile::Tile(float x, float y,float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect) {
	shape.setSize(sf::Vector2f{ gridSizeF, gridSizeF });
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(x, y);
	shape.setTexture(&texture);
	shape.setTextureRect(texture_rect);
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

void Tile::update()
{
}
