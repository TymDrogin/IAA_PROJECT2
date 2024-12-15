//
// Created by tim on 11/27/24.
//

#include <string.h>
#include <stdlib.h>
#include "alrogithm.h"

int* get_random_solution(const Data* data, const bool get_valid) {
    int* solution = (int*)malloc(sizeof(int) * data->coin_types_n);
    for (int i = 0; i < data->coin_types_n; i++) {
        solution[i] = rand() % RANGE_OF_RANDOM_NUMS_FOR_SOLUTION;
    }
	if (get_valid) {
		repair_solution(solution, data);
	};
    return solution;
}
Individual* get_random_population(const Data* data, const bool get_valid) {
	Individual* population = malloc(data->population_n * sizeof(Individual));
	for (int i = 0; i < data->population_n; i++) {
		population[i].solution = get_random_solution(data, get_valid);
		population[i].fitness = (float)INT_MAX;
		population[i].valid = is_valid_solution(population[i].solution, data);
	}
	return population;
}
void free_population(const Data* data, Individual* population) {
	for (int i = 0; i < data->population_n; i++) {
		free(population[i].solution);
	}
	free(population);
}

void repair_solution(int* sol, const Data* data) {
	if (sol == NULL) {
		exit(5);
	}

	int deviation = solution_target_diff(sol, data);
	if (deviation > 0) {
		for (int i = 0; i < data->coin_types_n; i++) {
			int coins_to_remove = deviation / data->coin_values_in_cents[i];
			if (sol[i] >= coins_to_remove) {
				sol[i] -= coins_to_remove;
			} else {
				sol[i] = 0;
			}
			deviation = solution_target_diff(sol, data);
			if (deviation <= 0) {
				break;
			}
		}
	}
	deviation = solution_target_diff(sol, data);
	if (deviation < 0) {
		for (int i = data->coin_types_n - 1; i >= 0; i--) {
			int coins_to_add = abs(deviation / data->coin_values_in_cents[i]);
			sol[i] += coins_to_add;

			deviation = solution_target_diff(sol, data);
			if (deviation >= 0) {
				break;
			}
		}
	}
}

int solution_cost(const int* solution, const Data* data, bool* valid) {
	// Penalize invalid solutions
	if (!is_valid_solution(solution, data)) {
		*valid = false;
		return INT_MAX;
	}
	*valid = true;
	return num_of_coins_used(solution, data);
}
int* generate_neighbor(const int* sol, const Data* data, int num_pos_to_mutate) {
	int* new_sol = (int*)malloc(sizeof(int) * data->coin_types_n);
	memcpy(new_sol, sol, data->coin_types_n * sizeof(int));


	// Array to hold the indices
	int indices[MAX_COINS];
	for (int i = 0; i < data->coin_types_n; i++) {
		indices[i] = i;
	}

	// Shuffle the indices using Fisher-Yates
	for (int i = data->coin_types_n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		// Swap indices[i] and indices[j]
		int temp = indices[i];
		indices[i] = indices[j];
		indices[j] = temp;
	}

	// Select the first random indicies indices
	if (num_pos_to_mutate > data->coin_types_n) {
		num_pos_to_mutate = data->coin_types_n;
	}


	int pos_to_mutate[MAX_COINS];
	for (int i = 0; i < num_pos_to_mutate; i++) {
		pos_to_mutate[i] = indices[i];
	}

	// Mutate solution
	for (int i = 0; i < num_pos_to_mutate; i++) {
		if (rand() % 2 == 0) {
			new_sol[pos_to_mutate[i]] += 1;
		} else {
			if (new_sol[pos_to_mutate[i]] - 1 >= 0) {
				new_sol[pos_to_mutate[i]] -= 1;
			} else {
				new_sol[pos_to_mutate[i]] = 0;
			}
		}
	}

	repair_solution(new_sol, data);
	return new_sol;
}

int hill_climbing(int* initial_solution, Data* data, int num_iter) {
	bool valid;
	int cost = solution_cost(initial_solution, data, &valid);
	for (int i = 0; i < num_iter; i++) {
		int* new_sol = generate_neighbor(initial_solution, data, 4);

		int costNeighbor = solution_cost(new_sol, data, &valid);
		if (costNeighbor <= cost) {
			cost = costNeighbor;
			memcpy(initial_solution, new_sol, data->coin_types_n * sizeof(int));
		}
		free(new_sol);
	}
	return cost;
}

float rand_01() {
	return (float)rand() / RAND_MAX;
}
void crossover(Individual* parents, const Data* data, Individual* offspring);
void crossover2(Individual* parents, const Data* data, Individual* offspring);
void crossover3(Individual* parents, const Data* data, Individual* offspring);
void mutation(Individual* offspring, const Data* data);
void mutation2(Individual* offspring, const Data* data);

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(Individual* pop, const Data* data, Individual* parents) {
	for (int i = 0; i < data->population_n; i++) {
		int x1, x2;

		x1 = rand() % data->population_n;
		do {
			x2 = rand() % data->population_n;
		} while (x1 == x2);

		// Minimize
		if (pop[x1].fitness < pop[x2].fitness) {
			parents[i] = pop[x1];
		} else {
			parents[i] = pop[x2];
		}
	}
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(Individual* parents, const Data* data, Individual* offspring) {
	// One-point crossover
	//crossover(parents, d, offspring);
	// Two-point crossover
	//crossover2(parents, d, offspring);
	// Uniform crossover
	crossover3(parents, data, offspring);
	// Binary mutation
	//mutation(offspring, data);
	// Mutation of permutations
	mutation2(offspring, data);
}

void crossover(Individual* parents, const Data* data, Individual* offspring) {
	for (int i = 0; i < data->population_n; i += 2) {
		if (rand_01() < data->crossover_chance) {
			int point = rand() % data->coin_types_n;
			for (int j = 0; j < point; j++) {
				offspring[i].solution[j] = parents[i].solution[j];
				offspring[i + 1].solution[j] = parents[i + 1].solution[j];
			}
			for (int j = point; j < data->coin_types_n; j++) {
				offspring[i].solution[j] = parents[i + 1].solution[j];
				offspring[i + 1].solution[j] = parents[i].solution[j];
			}
		} else {
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}
void crossover2(Individual* parents, const Data* data, Individual* offspring) {
	for (int i = 0; i < data->population_n; i += 2) {
		if (rand_01() < data->crossover_chance) {
			int p1, p2;
			p1 = rand() % data->coin_types_n;
			do {
				p2 = rand() % data->coin_types_n;
			} while (p2 == p1);

			if (p1 > p2) {
				int tmp = p1;
				p1 = p2;
				p2 = tmp;
			}

			for (int j = 0; j < p1; j++) {
				offspring[i].solution[j] = parents[i].solution[j];
				offspring[i + 1].solution[j] = parents[i + 1].solution[j];
			}
			for (int j = p1; j < p2; j++) {
				offspring[i].solution[j] = parents[i + 1].solution[j];
				offspring[i + 1].solution[j] = parents[i].solution[j];
			}
			for (int j = p2; j < data->coin_types_n; j++) {
				offspring[i].solution[j] = parents[i].solution[j];
				offspring[i + 1].solution[j] = parents[i + 1].solution[j];
			}
		} else {
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}
void crossover3(Individual* parents, const Data* data, Individual* offspring) {
	for (int i = 0; i < data->population_n; i += 2) {
		if (rand_01() < data->crossover_chance) {
			for (int j = 0; j < data->coin_types_n; j++) {
				if ((float)rand() / RAND_MAX >= 0.5f) {
					offspring[i].solution[j] = parents[i + 1].solution[j];
					offspring[i + 1].solution[j] = parents[i].solution[j];
				} else {
					offspring[i].solution[j] = parents[i].solution[j];
					offspring[i + 1].solution[j] = parents[i + 1].solution[j];
				}
			}
		} else {
			offspring[i] = parents[i];
			offspring[i + 1] = parents[i + 1];
		}
	}
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(Individual* offspring, const Data* data) {
	for (int i = 0; i < data->population_n; i++) {
		for (int j = 0; j < data->coin_types_n; j++) {
			if (rand_01() < data->mutation_chance) {
				offspring[i].solution[j] = !(offspring[i].solution[j]);
			}
		}
	}
}
// Mutation of permutations
void mutation2(Individual* offspring, const Data* data) {
	int p1, p2;

	for (int i = 0; i < data->population_n; i++) {
		if (rand_01() < data->mutation_chance) {
			p1 = rand() % data->coin_types_n;
			do {
				p2 = rand() % data->coin_types_n;
			} while (p2 == p1);
			
			int tmp = offspring[i].solution[p1];
			offspring[i].solution[p1] = offspring[i].solution[p2];
			offspring[i].solution[p2] = tmp;
		}
	}
}

void evaluate(Individual* population, const Data* data) {
	for (int i = 0; i < data->population_n; i++) {
		repair_solution(population[i].solution, data);
		population[i].fitness = solution_cost(population[i].solution, data, &population[i].valid);
	}
}