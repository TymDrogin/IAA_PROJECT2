#include <stdio.h>
#include <time.h>
#include <string.h>

#include "common-defines.h"
#include "data.h"
#include "helper_functions.h"
#include "file-handler.h"
#include "alrogithm.h"

void print_solution(int* solution, const Data* data) {
    for (int i = 0; i < data->coin_types_n; i++) {
        printf("%d ", solution[i]);
    }
    printf("\n");
}

int main(void) {
    srand(time(NULL));

    char filename[256];

    printf("Please provide the name of a data file: ");
    if (fgets(filename, sizeof(filename), stdin)) {
        // Remove trailing newline character if present
        filename[strcspn(filename, "\n")] = '\0';
    }
    printf("You entered: %s\n", filename);

    Data data;
    if (!read_file(&data, filename)) {
        printf("Error reading config file\n");
        exit(1);
    } else {
        print_data(&data);
    }

    float mbf;
    int best_sol[MAX_COINS];
    int i;

    int number_of_runs;
    printf("Please provide number of runs: ");
    fscanf(stdin, "%d", &number_of_runs);
    printf("Please provide population count: ");
    fscanf(stdin, "%d", &data.population_n);
    printf("Please provide number of generations: ");
    fscanf(stdin, "%d", &data.generations_n);
    printf("Please provide chance of mutation: ");
    fscanf(stdin, "%f", &data.mutation_chance);
    printf("Please provide chance of crossover: ");
    fscanf(stdin, "%f", &data.crossover_chance);

    printf("HILL CLIMBING\n\n");

    mbf = 0.0f;
    int best_cost = INT_MAX;
    for (i = 0; i < number_of_runs; i++) {
        printf("Run %d\n", i + 1);

        int* solution = get_random_solution(&data, false);
        printf("\nThe initial solution is: ");
        print_solution(solution, &data);

        int cost = hill_climbing(solution, &data, 20);
        printf("Current solution: ");
        print_solution(solution, &data);
        printf("With cost %d\n\n\n", cost);

        mbf += cost;
        if (i == 0 || cost < best_cost) {
            best_cost = cost;
            memcpy(best_sol, solution, data.coin_types_n * sizeof(int));
        }
        free(solution);
    }

    printf("MBF: %f\n", mbf / i);
    printf("Best solution: ");
    print_solution(best_sol, &data);
    printf("With cost %d\n\n", best_cost);

    printf("EVOLUTIONARY ALGORITHM\n\n");

    mbf = 0.0f;
    float best_fitness = (float)INT_MAX;
    for (i = 0; i < number_of_runs; i++) {
        printf("Run %d\n", i + 1);
        
        Individual* pop = get_random_population(&data, false);

        evaluate(pop, &data);

        Individual best_run = pop[0];
        best_run = get_best(pop, &data, best_run);
        
        Individual* parents = malloc(sizeof(Individual) * data.population_n);
        if (parents == NULL) {
            printf("Error allocating memory\n");
            exit(1);
        }

        int current_gen = 1;
        while (current_gen <= data.generations_n) {
            // Find parents
            tournament(pop, &data, parents);
            // Descendants are stored in pop
            genetic_operators(parents, &data, pop);
            evaluate(pop, &data);
            best_run = get_best(pop, &data, best_run);
            current_gen++;
        }

        int invalid_solutions = 0;
        for (int i = 0; i < data.population_n; i++) {
            if (pop[i].valid == false) invalid_solutions++;
        }

        best_run = get_best(pop, &data, best_run);
        printf("Best individual: ");
        print_solution(best_run.solution, &data);
        printf("With cost %f\n", best_run.fitness);

        printf("Percentage of invalid solutions: %f\n\n\n", 100 * (float)invalid_solutions / data.population_n);
        mbf += best_run.fitness;
        if (i == 0 || best_run.fitness < best_fitness) {
            best_fitness = best_run.fitness;
            memcpy(best_sol, best_run.solution, data.coin_types_n * sizeof(int));
        }
        
        free(parents);
        //free_population(&data, pop);
    }

    printf("MBF: %f\n", mbf / i);
    printf("Best solution: ");
    print_solution(best_sol, &data);
    printf("With cost %f\n\n", best_fitness);

    printf("HYBRID ALGORITHMS\n\n");

    mbf = 0.0f;
    best_fitness = (float)INT_MAX;
    for (i = 0; i < number_of_runs; i++) {
        printf("Run %d\n", i + 1);

        Individual* pop = get_random_population(&data, false);

        evaluate(pop, &data);
        
        for (int k = 0; k < data.population_n; k++) {
            pop[k].fitness = hill_climbing(pop[k].solution, &data, 5000);
        }

        Individual best_run = pop[0];
        best_run = get_best(pop, &data, best_run);

        Individual* parents = malloc(sizeof(Individual) * data.population_n);
        if (parents == NULL) {
            printf("Error allocating memory\n");
            exit(1);
        }
        int current_gen = 1;
        while (current_gen <= data.generations_n) {
            // Find parents
            tournament(pop, &data, parents);
            // Descendants are stored in pop
            genetic_operators(parents, &data, pop);
            evaluate(pop, &data);
            best_run = get_best(pop, &data, best_run);
            current_gen++;
        }

        int invalid_solutions = 0;
        for (int i = 0; i < data.population_n; i++) {
            if (pop[i].valid == false) invalid_solutions++;
        }
        
        for (int k = 0; k < data.population_n; k++) {
            pop[k].fitness = hill_climbing(pop[k].solution, &data, 5000);
        }

        best_run = get_best(pop, &data, best_run);
        printf("Best individual: ");
        print_solution(best_run.solution, &data);
        printf("With cost %f\n", best_run.fitness);

        printf("Percentage of invalid solutions: %f\n\n\n", 100 * (float)invalid_solutions / data.population_n);
        mbf += best_run.fitness;
        if (i == 0 || best_run.fitness < best_fitness) {
            best_fitness = best_run.fitness;
            memcpy(best_sol, best_run.solution, data.coin_types_n * sizeof(int));
        }

        free(parents);
        //free_population(&data, pop);
    }

    printf("MBF: %f\n", mbf / i);
    printf("Best solution: ");
    print_solution(best_sol, &data);
    printf("With cost %f\n\n", best_fitness);

    return 0;
}