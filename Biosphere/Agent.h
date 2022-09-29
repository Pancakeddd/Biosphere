#pragma once

#include "Genome.h"
#include "Environment.h"

struct Agent : TileImplementation<Agent>
{
	const static TileType s_type = TileType::AGENT;

	void tick(size_t x, size_t y, Map* m);
	void unfold();

private:
	Genome p_genome;
	Phenotype p_phenotype;
};