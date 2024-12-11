//
// Created by tim on 11/27/24.
//

#include "alrogithm.h"
#include <stdlib.h>

int* random_solution(Data* data) {
    int* solution = (int*)malloc(sizeof(int) * data->coin_types_n);
    for (int i = 0; i < data->coin_types_n; i++) {
        solution[i] = rand() % 10;
    }
    return solution;
}

