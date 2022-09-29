#pragma once

#include "Genome.h"
#include "Environment.h"
#include "VM.h"

struct Agent : TileImplementation<Agent>
{
	const static TileType s_type = TileType::AGENT;
	const static bool s_can_draw = true;

	void tick(size_t x, size_t y, Map* m);
	void draw(size_t x, size_t y, Map* m);
	void unfold();

private:
	void loadInputs();
	void loadCode();

	Genome p_genome;
	Phenotype p_phenotype;
	VM vm;
};