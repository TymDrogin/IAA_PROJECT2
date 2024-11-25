#include <stdio.h>

#include "common-defines.h"
#include "config.h"
#include "helper_functions.h"
#include "file-handler.h"


int main(void) {

    int solution[BASE_COIN_TYPES_NUM] = {0, 0, 0, 2};

    bool is_valid = is_valid_solution(solution, BASE_COINS, BASE_COIN_TYPES_NUM, 100);

    char* filename = "test.txt";
    Config config;
    if (!read_file(&config, filename)) {
        printf("Error reading config file\n");
    } else {
        print_config(&config);
    }

    if (is_valid) {
        printf("Valid solution\n");
    } else {
        printf("Invalid solution\n");
    }
    return 0;
}