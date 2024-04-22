#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING, ABOVE,ENEMYSPAWNER };
class Tile
{
private:
protected:
	sf::Sprite shape;
public:

	virtual ~Tile();
	Tile();
	Tile(short type,int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, const bool collision = false);
	virtual  void render(sf::RenderTarget& target, sf::Vector2f playerPos = sf::Vector2f{}, sf::Shader* shader = nullptr) const = 0;
	virtual void update() = 0;
	//the type of tile we are saving
	short type;
	//does the tile support collisions
	bool collision;
	virtual  const bool& getCollision() const;
	virtual const sf::Vector2f& getPosition() const;
	//checks if the tile has collisions activated
	virtual  const bool intersects(const sf::FloatRect bounds) const;
	const sf::FloatRect getGlobalBounds() const;
	//ACCESSORS
	const short& getType() const;
	virtual const std::string getAsString() const = 0;
};




#endif