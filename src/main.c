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

    int* solution = random_solution(&data);
    printf("\nThe initial solution is: ");
    print_solution(solution, &data);
    printf("\n");

    for (int i = 0; i < 10; i++) {
        int cost = hill_climbing(solution, &data, /*TODO let user specify iteration count?*/10);
        printf("Current solution: ");
        print_solution(solution, &data);
        printf("With cost %d\n\n", cost);
    }

    return 0;
}