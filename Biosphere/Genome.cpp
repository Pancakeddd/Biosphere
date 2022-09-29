#include "Genome.h"

Phenotype Genome::unfold(size_t iteration)
{
	Phenotype phenotype = Phenotype(genome);

	for (size_t i = 0; i < iteration; ++i)
	{
		auto next_phenotype = Phenotype(phenotype);

		for (size_t bit_i = 0; bit_i < phenotype.size(); ++bit_i)
		{
			applyAllRules(bit_i, phenotype, next_phenotype);
		}

		phenotype = next_phenotype;
	}

	return phenotype;
}

void Genome::applyAllRules(size_t idx, const Phenotype& phenotype, Phenotype& output_phenotype)
{
	for (const Rule& rule : rules)
	{
		// Match the rule to the index
		bool failed_match = false;

		for (size_t rule_bit = 0; rule_bit < rule.from_size; rule_bit++)
		{
			if (rule.from_capture[rule_bit] != phenotype[(idx+rule_bit)%phenotype.size()])
			{
				failed_match = true;
				break;
			}
		}

		if (!failed_match)
		{
			// Match worked! output 'to_capture' to output_phenotype
			for (size_t rule_bit = 0; rule_bit < rule.to_size; rule_bit++)
			{
				output_phenotype[(idx + rule_bit) % phenotype.size()] = rule.to_capture[rule_bit];
			}

			break; // finished applying.
		}
	}
}

Genome randomGenome(size_t rules_amount)
{
	Genome g;

	randomizeBitset(g.genome);

	for (size_t rule = 0; rule < rules_amount; ++rule)
	{
		Rule r;

		randomizeBitset(r.from_capture);
		randomizeBitset(r.to_capture);

		r.from_size = std::max(1, rand() % maxfrom);
		r.to_size = std::max(1, rand() % maxto);

		g.rules.push_back(r);
	}

	return g;
}
