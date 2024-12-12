#include <stdio.h>
#include <time.h>
#include <string.h>

#include "common-defines.h"
#include "data.h"
#include "helper_functions.h"
#include "file-handler.h"
#include "alrogithm.h"

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
    printf("The solution is: %d %d %d ", solution[0], solution[1], solution[2]);

    return 0;
}