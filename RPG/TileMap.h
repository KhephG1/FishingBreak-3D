#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include "Entity.h"
#include <xutility>
#include <xutility>
#include <locale>
class TileMap
{
private:
	void clear();
	sf::Vector2i maxSizeGrid;
	sf::Vector2f maxWorldSize;
	float gridSizeF = 50.f;
	int gridSizeI;
	int layers;
	std::vector< std::vector < std::vector<std::vector<Tile*>> > > tMap;
	//store tiles to be rendered above the player
	std::stack<Tile*> deferredRenderTiles;
	sf::Texture tileSheet;
	std::string textureFile;
	sf::RectangleShape collision_box;
	//Culling variables
	int from_x;
	int to_x;
	int from_y;
	int to_y;
public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();
	void update();
	void render(sf::RenderTarget& target,const sf::Vector2i gridPosition, const bool show_collision = false);
	//used to render tiles above the player
	void DeferredRender(sf::RenderTarget& target);
	void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool collision, const short type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	const sf::Texture* getileSheet() const;

	void updateCollision(Entity* entity, const float& dt);

	//Accessors
	const int getLayer(const int x, const int y, const int layer) const;
};
#endif
