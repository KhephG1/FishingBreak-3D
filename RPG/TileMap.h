#ifndef TILEMAP_H
#define TILEMAP_H
#include "Entity.h"
#include "EnemySpawner.h"
#include "RegularTile.h"
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
	TileMap(const std::string file_name);
	virtual ~TileMap();
	void render(sf::RenderTarget& target, const sf::Vector2i gridPosition, const bool show_collision = false, sf::Vector2f playerPos = sf::Vector2f{}, sf::Shader* shader = nullptr);
	//used to render tiles above the player
	void DeferredRender(sf::RenderTarget& target, sf::Vector2f playerPos =  sf::Vector2f{}, sf::Shader* shader = nullptr);
	void addTile(const int x, const int y, const int z, const sf::IntRect texture_rect, const bool collision, const short type);
	void removeTile(const int x, const int y, const int z, const int typ = -1);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	const sf::Texture* getileSheet() const;

	void update(Entity* entity, const float& dt);

	//Accessors
	const int getLayer(const int x, const int y, const int layer) const;
	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeFloat() const;
	const bool hasTile(const int x, const int y, const int z);
	const bool checkType(const int type, const int x, const int y, const int z) const;
};
#endif
