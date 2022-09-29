#include "Agent.h"

void Agent::loadInputs()
{
	vm.input[0] = randb();
}

void Agent::tick(size_t x, size_t y, Map* m)
{
	if (frame == 0) // Starting frame.
	{
		unfold();
		tile_color = RED;
	}

	loadInputs();

	vm.runNextCommand();

	tick_frame();
}

void Agent::draw(size_t x, size_t y, Map* m)
{
	Tile::draw(x, y, m);

	const auto &current_command = vm.src[vm.src_idx];

	DrawText(TextFormat("%d, %d", current_command.type, current_command.arg1), x * MAP_GRID_SIZE, y * MAP_GRID_SIZE, 10, BLUE);

	auto stack = vm.stack;

	for (size_t i = 0; i < stack.size(); ++i)
	{
		auto stack_top = stack.top();
		DrawText(TextFormat("%f", stack_top), x * MAP_GRID_SIZE, (y * MAP_GRID_SIZE) + (i + 1) * 5, 5, BLUE);
		stack.pop();
	}
}

void Agent::unfold()
{
	p_genome = randomGenome(0);
	p_phenotype = p_genome.unfold();
	loadCode();
}

void Agent::loadCode()
{
	constexpr static int ksize = 8;

	for (size_t i = 0; i < p_phenotype.size(); i += ksize)
	{
		auto opfield = Phenotype();
		auto argfield = Phenotype();
		opfield[i % ksize] = p_phenotype[i];
		opfield[(i + 1) % ksize] = p_phenotype[i + 1];
		opfield[(i + 2) % ksize] = p_phenotype[i + 2];
		opfield[(i + 3) % ksize] = p_phenotype[i + 3];

		argfield[(i) % ksize] = p_phenotype[i + 4];
		argfield[(i + 1) % ksize] = p_phenotype[i + 5];
		argfield[(i + 2) % ksize] = p_phenotype[i + 6];
		argfield[(i + 3) % ksize] = p_phenotype[i + 7];

		auto code = Opcode(opfield.to_ulong() % Opcode::OPSSIZE+1);

		vm.src[i / ksize].type = code;

		switch (code)
		{
		case PUSH_INPUT:
		{
			vm.src[i / ksize].idx = argfield.to_ulong() % INPUTS;
			break;
		}

		case SET_OUTPUT:
		{
			vm.src[i / ksize].idx = argfield.to_ulong() % OUTPUTS;
			break;
		}

		default: 
		{
			vm.src[i / ksize].arg1 = argfield.to_ulong();
		}

		}
	}
}
