//
// Created by tim on 11/27/24.
//

#ifndef ALROGITHM_H
#define ALROGITHM_H
#include <limits.h>

#include "helper_functions.h"
#include "data.h"
#include "common-defines.h"
#include "data.h"

typedef struct Individual {
	int* solution;
	float fitness;
	bool valid;
} Individual;

int* get_random_solution(const Data* data, const bool get_valid);
Individual* get_random_population(const Data* data, const bool get_valid);
void free_population(const Data* data, Individual* population);

int hill_climbing(int* sol, Data* data, int nIter);
void repair_solution(int* sol, const Data* data);

void tournament(Individual* pop, const Data* data, Individual* parents);
void genetic_operators(Individual* parents, const Data* data, Individual* offspring);
void evaluate(Individual* population, const Data* data);

#endif //ALROGITHM_H
