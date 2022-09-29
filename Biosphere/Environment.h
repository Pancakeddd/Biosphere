#pragma once

#include "Prelude.h"

#include <omp.h>

enum TileType
{
	NONE,
	AGENT
};

#define MAP_WIDTH 200
#define MAP_HEIGHT 200
#define MAP_GRID_SIZE 2

struct Map;

struct Tile
{
	virtual void tick(size_t x, size_t y, Map *m) {};
	virtual void draw(size_t x, size_t y, Map* m) {
		if (!canDraw())
			return;

		DrawCircle(x * MAP_GRID_SIZE * 2, y * MAP_GRID_SIZE * 2, MAP_GRID_SIZE, tile_color);
	};
	virtual TileType getType() = 0;
	virtual bool canDraw() = 0;
	//virtual ~Tile() = default;

	size_t frame = 0;

	Color tile_color = BLACK;

	template <class T> 
	std::shared_ptr<T> as()
	{
		return static_cast<T>(this);
	}

	void tick_frame()
	{
		frame++;
	}
};

using TileP = std::unique_ptr<Tile>;

template <class T>
struct TileImplementation : Tile
{
	TileType getType()
	{
		return T::s_type;
	}

	bool canDraw()
	{
		return T::s_can_draw;
	}
};

struct NoTile : TileImplementation<NoTile>
{
	const static TileType s_type = TileType::NONE;
	const static bool s_can_draw = false;
};

struct Map
{
	TileP &at(size_t x, size_t y);
	
	template <class T>
	Tile* create(size_t x, size_t y)
	{
		return (at(x, y) = std::move(std::make_unique<T>())).get();
	}
	void destroy(size_t x, size_t y);
	void clear();
	void draw();
	void tick();
	auto for_each_tile(auto f)
	{
//#pragma omp parallel for
		for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i)
		{
			size_t y = i / MAP_WIDTH;
			size_t x = i % MAP_WIDTH;
			f(x, y);
		}
	}

	auto for_each_tile_omp(auto f)
	{
		#pragma omp parallel for
		for (int i = 0; i < MAP_HEIGHT * MAP_WIDTH; ++i)
		{
			size_t y = i / MAP_WIDTH;
			size_t x = i % MAP_WIDTH;
			f(x, y);
		}
	}


	Map()
	{
		clear();
	}

private:
	TileP p_map[MAP_WIDTH * MAP_HEIGHT];
};

