#include "stdafx.h"
#include "TileMap.h"

TileMap::~TileMap()
{
	for (size_t x = 0; x < maxSize.x; x++) {
		for (size_t y{}; y < maxSize.y; y++) {
			for (size_t z{}; z < layers; z++) {
				delete tMap.at(x).at(y).at(z);
			}
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : tMap) {
		for (auto& y : x) {
			for (auto& z : y) {
				if (z!=nullptr) {
					z->render(target);
				}
			}
		}
	}
}

void TileMap::addTile(const unsigned x, unsigned y, const unsigned z, const sf::IntRect texture_rect)
{
	//Takes 2 indices from the mouse position in the grid and adds a tile to that position
	if (x < maxSize.x && y < maxSize.y && z<layers && x >=0 && y>=0 && z>=0) {
		if (tMap.at(x).at(y).at(z) == nullptr) { // if the tile at this index is empty, we can add a tile
			tMap.at(x).at(y).at(z) = new Tile(x * gridSizeF, y * gridSizeF, gridSizeF, tileSheet, texture_rect);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < maxSize.x && y < maxSize.y && z < layers && x >= 0 && y >= 0 && z >= 0) {
		if (tMap.at(x).at(y).at(z) != nullptr) { // if the tile at this index is empty, we can remove a tile
			delete tMap.at(x).at(y).at(z);
			tMap.at(x).at(y).at(z) = nullptr;
		}
	}
}

const sf::Texture* TileMap::getileSheet() const
{
	return &tileSheet;
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height) {
	gridSizeU = (unsigned)gridSize;
	maxSize.x = width;
	maxSize.y = height;
	layers = 1;
	gridSizeF = gridSize;
	gridSizeU = (unsigned)gridSizeF;
	tMap.reserve(maxSize.x);
	for (size_t x = 0; x < maxSize.x; x++) {
		tMap.push_back(std::vector<std::vector<Tile*>> {});
		for (size_t y{}; y < maxSize.y; y++) {
			tMap.reserve(maxSize.y);
			tMap.at(x).push_back(std::vector<Tile*>{});
			for (size_t z{}; z < layers; z++) {
				tMap.at(x).at(y).reserve(layers);
				tMap.at(x).at(y).push_back(nullptr);
			}
		}
	}
	if (!tileSheet.loadFromFile("Resources/Images/Tiles/GRASS+.png")) {
		throw std::runtime_error{ "ERROR" };
	}
}
