//
// Created by tim on 11/24/24.
//

#include "file-handler.h"

bool read_file(Data* data, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

    int N;
    if (fscanf(file, "%d", &N) != 1) {
        fprintf(stderr, "Can't get array size\n");
        fclose(file);
        return false;
    }

    float V;
    if (fscanf(file, "%f", &V) != 1) {
        fprintf(stderr, "Can't read target sum\n");
        fclose(file);
        return false;
    }

    float *base_coins = malloc(N * sizeof(float));
    if (!base_coins) {
        perror("Memory allocation failed");
        fclose(file);
        return false;
    }

    // Read the base coins values
    for (int i = 0; i < N; i++) {
        if (fscanf(file, "%f", &base_coins[i]) != 1) {
            fprintf(stderr, "Error reading array element %d.\n", i);
            free(base_coins);
            fclose(file);
            return false;
        }
    }

    // convert base coins to cents

    int* base_coins_in_cents = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        base_coins_in_cents[i] = cents_from_euros(base_coins[i]);
    }
    free(base_coins);

    data->coin_types_n = N;
    data->target_sum_in_cents = cents_from_euros(V);
    data->coin_values_in_cents = base_coins_in_cents;

    fclose(file);
    return true;
}