#pragma once

#include <bitset>
#include <vector>

#include "Prelude.h"

const constexpr auto maxfrom = 5;
const constexpr auto maxto = 5;

const constexpr size_t base_genome_size = 500;

struct Phenotype : std::bitset<base_genome_size>
{
	using std::bitset<base_genome_size>::bitset;

	Phenotype(const std::bitset<base_genome_size>& o_genome) : std::bitset<base_genome_size>(o_genome)
	{
	}

	Phenotype() = default;
};

struct Rule
{
	std::bitset<maxfrom> from_capture;
	std::bitset<maxto> to_capture;
	size_t from_size;
	size_t to_size;
};

struct Genome
{
	std::bitset<base_genome_size> genome;
	std::vector<Rule> rules;

	Phenotype unfold(size_t iterations = 10);
private:

	void applyAllRules(size_t idx, const Phenotype& phenotype, Phenotype& output_phenotype);
};

template<size_t s>
inline void randomizeBitset(std::bitset<s>& bitset)
{
	for (size_t idx = 0; idx < bitset.size(); ++idx)
	{
		bitset[idx] = randb();
	}
}


Genome randomGenome(size_t rules_amount);