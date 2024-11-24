#include <stdio.h>

#include "common-defines.h"
#include "helper_functions.h"


int main(void) {

    int solution[COIN_TYPES_NUM] = {2, 0, 2, 1};

    bool is_valid = is_valid_solution(solution, BASE_COINS, 100);

    if (is_valid) {
        printf("Valid solution\n");
    } else {
        printf("Invalid solution\n");
    }
    return 0;
}