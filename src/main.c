#include <stdio.h>

#include "common-defines.h"
#include "helper_functions.h"


int main(void) {

    int solution[BASE_COIN_TYPES_NUM] = {0, 0, 0, 2};

    bool is_valid = is_valid_solution(solution, BASE_COINS, 4, 100, 6);

    if (is_valid) {
        printf("Valid solution\n");
    } else {
        printf("Invalid solution\n");
    }
    return 0;
}