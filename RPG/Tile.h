#ifndef TILE_H
#define TILE_H

enum TileTypes { DEFAULT = 0, DAMAGING, ABOVE };
class Tile
{
private:
protected:
	sf::Sprite shape;
public:

	virtual ~Tile();
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect, bool collision= false, short type = DEFAULT);
	void render(sf::RenderTarget& target, sf::Vector2f playerPos = sf::Vector2f{}, sf::Shader* shader = nullptr);
	void update();
	//the type of tile we are saving
	short type;
	//does the tile support collisions
	bool collision;
	friend std::ostream& operator<<(std::ostream& stream, Tile tile);
	const sf::Vector2f& getPosition() const;
	//checks if the tile has collisions activated
	const bool& getCollision() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const sf::FloatRect getGlobalBounds() const;
	//ACCESSORS
	const short& getType() const;
};

std::ostream& operator<<(std::ostream& stream, Tile tile);

#endif