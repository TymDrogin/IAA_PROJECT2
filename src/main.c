#include <stdio.h>
#include <time.h>

#include "common-defines.h"
#include "data.h"
#include "helper_functions.h"
#include "file-handler.h"

int main(void) {
    // Init RNG
    srand((unsigned int)time(NULL));

    //char* filename = "test.txt";
    char filename[1024];
    Data data;

    printf("Please provide the name of a data file:");
    gets(filename);

    if (!read_file(&data, filename)) {
        printf("Error reading config file\n");
        exit(1);
    } else {
        print_data(&data);
    }

    return 0;
}