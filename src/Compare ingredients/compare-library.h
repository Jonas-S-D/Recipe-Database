// Created by Kristoffer Holm on 20/11/2023.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER 2048


FILE *open_file(char *file, char *mode);

unsigned int file_length(FILE *file);

char *stored_to_array();

char ***recipe_to_array();

void count_row_col(FILE *f, char *r_buffer, unsigned int *rows, unsigned int *col);

char ***Allocate_array(unsigned int rows, unsigned int cols);

char ***populate_array(FILE *file, char *recipe_buffer, char ***recipe_array);


