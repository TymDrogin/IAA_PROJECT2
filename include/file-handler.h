//
// Created by tim on 11/24/24.
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

#include "common-defines.h"
#include "helper_functions.h"
#include "config.h"


bool read_file(Config* config, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return false;
    }

}




#endif //FILE_HANDLER_H
