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


void repair_solution(int* sol, Data* data) {
	int deviation = solution_target_diff(sol, data);





}






int solution_cost(const int* solution, const Data* data) {
	// Penalize invalid solutions
	// TODO try doing repair instead if we have time
	if (!is_valid_solution(solution, data)) return INT_MAX;
	return num_of_coins_used(solution, data);
}
int* generate_neighbor(const int* sol, const Data* data) {
	int* new_sol = (int*)malloc(sizeof(int) * data->coin_types_n);
	memcpy(new_sol, sol, data->coin_types_n * sizeof(int));

	// Random positions to mutate
	int pos1, pos2, pos3, pos4;
	pos1 = rand() % data->coin_types_n;
	// Make sure positions are different
	do {
		pos2 = rand() % data->coin_types_n;
	} while (pos2 == pos1 || new_sol[pos2] <= 0);
		
	pos3 = rand() % data->coin_types_n;
	// Make sure positions are different
	do {
		pos4 = rand() % data->coin_types_n;
	} while (pos4 == pos3 || new_sol[pos4] <= 0);

	new_sol[pos1]++;
	new_sol[pos2]--;
	new_sol[pos3]++;
	new_sol[pos4]--;

	return new_sol;
}

int hill_climbing(int* initial_solution, Data* data, int num_iter) {
	int cost = solution_cost(initial_solution, data);
	for (int i = 0; i < num_iter; i++) {
		int* new_sol = generate_neighbor(initial_solution, data);

		int costNeighbor = solution_cost(new_sol, data);
		if (costNeighbor <= cost) {
			cost = costNeighbor;
			memcpy(initial_solution, new_sol, data->coin_types_n * sizeof(int));
		}
		free(new_sol);
	}
	return cost;
}