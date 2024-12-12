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
void generate_neighbor(int* sol, int* newSol, int solSize) {
	memcpy(newSol, sol, solSize * sizeof(int));
	// TODO
}

int hill_climbing(int* sol, Data* data, int nIter) {
	int* newSol = malloc(data->coin_types_n * sizeof(int));
	if (newSol == NULL) {
		exit(-1);
	}


	int cost = evaluate_solution(sol, data);
	for (int i = 0; i < nIter; i++) {
		generate_neighbor(sol, newSol, data->coin_types_n);

		int costNeighbor = evaluate_solution(newSol, data);
		if (costNeighbor <= cost) {
			cost = costNeighbor;
			memcpy(sol, newSol, data->coin_types_n * sizeof(int));
		}
	}

	free(newSol);
	return cost;
}