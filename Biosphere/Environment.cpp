#include "Environment.h"

TileP &Map::at(size_t x, size_t y)
{
	/*if (x < 0 || x >= MAP_WIDTH ||
		y < 0 || y >= MAP_HEIGHT)
		return nullptr;*/

	return p_map[y * MAP_WIDTH + x];
}

void Map::destroy(size_t x, size_t y)
{
	at(x, y).reset();
	create<NoTile>(x, y);
}

void Map::clear()
{
	for (auto &tile : p_map)
	{
		tile.reset();
		tile = std::move(std::make_unique<NoTile>());
	}
}

void Map::draw()
{
	for_each_tile(
		[this](size_t x, size_t y)
		{
			at(x, y)->draw(x, y, this);
		});
}

void Map::tick()
{
	for_each_tile_omp(
		[this](size_t x, size_t y)
		{
			at(x, y)->tick(x, y, this);
		});
}
