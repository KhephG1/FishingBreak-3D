#ifndef TILE_H
#define TILE_H
class Tile
{
private:
protected:
	sf::RectangleShape shape;


public:
	virtual ~Tile();
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect texture_rect);
	void render(sf::RenderTarget& target);
	void update();
};

#endif