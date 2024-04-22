#ifndef REGULARTILE_H
#define REGULARTILE_H
#include "Tile.h"
class RegularTile :
    public Tile
{

private:
protected:
public:

	virtual ~RegularTile();
	RegularTile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, bool collision = false);
	virtual  void render(sf::RenderTarget& target, sf::Vector2f playerPos = sf::Vector2f{}, sf::Shader* shader = nullptr) const;
	virtual void update();;
	//checks if the tile has collisions activated
	
	//ACCESSORS
	virtual const std::string getAsString() const;
};



#endif