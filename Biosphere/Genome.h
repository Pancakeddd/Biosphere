#pragma once

#include <bitset>
#include <map>

#include "Prelude.h"

const constexpr auto maxfrom = 5;
const constexpr auto maxto = 5;

const constexpr size_t base_genome_size = 32*8;

using Phenotype = std::bitset<base_genome_size>;

struct Genome
{
	std::bitset<base_genome_size> genome;
	std::map<int, bool> codons;

	Phenotype unfold();
private:
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