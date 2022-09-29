#include "Agent.h"

void Agent::tick(size_t x, size_t y, Map* m)
{
	if (frame == 0) // Starting frame.
	{
		unfold();
	}

	tile_color = RED;

	tick_frame();
}

void Agent::unfold()
{
	p_phenotype = p_genome.unfold(100);
}
