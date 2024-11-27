#include <stdio.h>

#include "common-defines.h"
#include "data.h"
#include "helper_functions.h"
#include "file-handler.h"


int main(void) {
    char* filename = "test.txt";
    Data data;

    printf("Please provide the name of a data file:");


    if (!read_file(&data, filename)) {
        printf("Error reading config file\n");
        exit(1);
    } else {
        print_data(&data);
    }

    return 0;
}