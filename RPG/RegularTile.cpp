#include "stdafx.h"
#include "RegularTile.h"

RegularTile::~RegularTile()
{
}

RegularTile::RegularTile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, bool collision) : Tile{type, grid_x, grid_y,gridSizeF,texture, texture_rect,collision}
{
}
void RegularTile::render(sf::RenderTarget& target, sf::Vector2f playerPos, sf::Shader* shader) const
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
void RegularTile::update()
{
}

const std::string RegularTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;

	std::cout << ss.str() << "\n";

	return ss.str();

}