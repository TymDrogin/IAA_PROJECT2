//
// Created by tim on 11/27/24.
//

#include <string.h>
#include <stdlib.h>
#include "alrogithm.h"

int* random_solution(Data* data) {
    int* solution = (int*)malloc(sizeof(int) * data->coin_types_n);
    for (int i = 0; i < data->coin_types_n; i++) {
        solution[i] = rand() % RANGE_OF_RANDOM_NUMS_FOR_SOLUTION;
    }
    return solution;
}

int evaluate_solution(int* solution, Data* data) {
	// Penalize invalid solutions
	// TODO try doing repair instead if we have time
	if (!is_valid_solution(solution, data)) return INT_MAX;
	return num_of_coins_used(solution, data);
}
void generate_neighbor(int* sol, int* new_sol, int sol_size) {
	memcpy(new_sol, sol, sol_size * sizeof(int));
	
	int pos1 = rand() % sol_size;
	int pos2;
	do {
		pos2 = rand() % sol_size;
	} while (pos2 == pos1);

	new_sol[pos1]++;
	new_sol[pos2]--;
}

int hill_climbing(int* sol, Data* data, int nIter) {
	int* new_sol = malloc(data->coin_types_n * sizeof(int));
	if (new_sol == NULL) {
		exit(-1);
	}


	int cost = evaluate_solution(sol, data);
	for (int i = 0; i < nIter; i++) {
		generate_neighbor(sol, new_sol, data->coin_types_n);

		int costNeighbor = evaluate_solution(new_sol, data);
		if (costNeighbor <= cost) {
			cost = costNeighbor;
			memcpy(sol, new_sol, data->coin_types_n * sizeof(int));
		}
	}

	free(new_sol);
	return cost;
}