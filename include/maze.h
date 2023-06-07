#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef STRUCT_H
#define STRUCT_H

struct maze{
    char **maze;
    int rows;
    int columns;
    char wall_char;
    char empty_char;
    char step_char;
    char enter;
    char exit;
        
    int enterRow;
    int enterCol;
    int exitRow;
    int exitCol;
};

struct position {
    int x, y;
};

#endif