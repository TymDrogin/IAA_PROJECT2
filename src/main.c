#include <stdio.h>

#include "common-defines.h"
#include "helper_functions.h"


int main(void) {

    int solution[COIN_TYPES_NUM] = {4, 1, 1, 1};

    bool is_valid = is_valid_solution(solution, BASE_COINS, 100, 6);

    if (is_valid) {
        printf("Valid solution\n");
    } else {
        printf("Invalid solution\n");
    }
    return 0;
}