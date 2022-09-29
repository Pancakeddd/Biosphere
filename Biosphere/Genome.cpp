#include "Genome.h"

Phenotype Genome::unfold()
{
	Phenotype phenotype = Phenotype(genome);
	
	bool is_codon_active = false;

	for (size_t i = 0; i < phenotype.size(); ++i)
	{
		if (codons[i])
		{
			is_codon_active = !is_codon_active;
		}

		if (is_codon_active)
		{
			phenotype[i] = false;
		}
	}

	return phenotype;
}

Genome randomGenome(size_t rules_amount)
{
	Genome g;

	randomizeBitset(g.genome);

	return g;
}
