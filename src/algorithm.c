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


void repair_solution(int* sol, const Data* data) {
	int deviation = solution_target_diff(sol, data);
	while (deviation != 0) {
		if (deviation > 0) {
			// Decrement solution starting with smaller coins
			for (int i = 0; i < data->coin_types_n; i++) {
				if (sol[i] > 0) {
					// For each coin value try to remove the maximum number of them possible (lowers the cost)
					int max_n_of_coins_to_remove = deviation / data->coin_values_in_cents[i];
					int n_to_remove = (max_n_of_coins_to_remove > sol[i]) ? sol[i] : max_n_of_coins_to_remove;
					sol[i] -= n_to_remove;
					deviation = solution_target_diff(sol, data);

					if (deviation == 0) break; // Stop early if target is reached
				}
			}
		} else {
			// Increment solution starting with bigger coins (lowers the cost)
			for (int i = data->coin_types_n - 1; i >= 0; i--) {
				// For each coin value try to add the maximum number of them possible
				int max_n_of_coins_to_add = -deviation / data->coin_values_in_cents[i];
				sol[i] += max_n_of_coins_to_add;
				deviation = solution_target_diff(sol, data);

				if (deviation == 0) break; // Stop early if target is reached
			}
		}
	}
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

	// first random position to mutate
	int pos1 = rand() % data->coin_types_n;
	// first random position to mutate
	int pos2;
	// Make sure positions are different
	do {
		pos2 = rand() % data->coin_types_n;
	} while (pos2 == pos1);

	new_sol[pos1]++;
	new_sol[pos2]--;

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