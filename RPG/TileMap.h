#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
class TileMap
{
private:
	sf::Vector2u maxSize;
	float gridSizeF = 50.f;
	unsigned gridSizeU;
	unsigned layers;
	std::vector< std::vector < std::vector<Tile*> > > tMap;
	sf::Texture tileSheet;
public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();
	void update();
	void render(sf::RenderTarget& target);
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getileSheet() const;
};
#endif
