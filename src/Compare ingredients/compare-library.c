// Created by Kristoffer Holm on 20/11/2023.
#include "compare-library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *open_file(char *file, char *mode) {
    FILE *f = fopen(file, mode);
    if (!f) {
        perror(file);
        exit(EXIT_FAILURE);
    }
    return f;
}

unsigned int file_length(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    return length;
}

char *stored_to_array() {
    char stored_buffer[BUFFER];
    // Opens the file and check if the file opens.
    FILE *stored = open_file("../stored.csv", "r");

    // Counts the number of characters in the file.
    unsigned int length = file_length(stored);

    // Allocates an array with the length of the csv file.
    char **stored_arr = (char **) malloc((length + 1) * sizeof(char *));
    int i = 0;
    while (fgets(stored_buffer, BUFFER, stored)) {
        char *stored_string = strtok(stored_buffer, ", \n");

        while (stored_string != NULL) {
            stored_arr[i] = (char *) malloc((strlen(stored_string) + 1) * sizeof(char));
            strcpy(stored_arr[i], stored_string);

            //printf("%s\n", stored_arr[i]);

            stored_string = strtok(NULL, ", \n");
            ++i;
        }
    }
    fclose(stored);
    return (char *) stored_arr;
}

char ***recipe_to_array() {
    char recipe_buffer[BUFFER];

    // Opens the file and check if it opens
    FILE *recipe = open_file("../Recipe.csv", "r");

    // Count the number of rows and columns
    unsigned int num_rows = 0, num_cols = 0;
    count_row_col(recipe, recipe_buffer, &num_rows, &num_cols);

    // Reset file pointer to the beginning of the file
    fseek(recipe, 0, SEEK_SET);

    // Allocate memory for the 2D array
    char ***recipe_arr = Allocate_array(num_rows, num_cols);

    // Populate the 2D array
    populate_array(recipe, recipe_buffer, recipe_arr);

    // Close the file;
    fclose(recipe);

    // return the recipe array.
    return recipe_arr;
}

char ***Allocate_array(unsigned int rows, unsigned int cols) {
    char ***recipe_arr = (char ***) malloc(rows * sizeof(char **) + rows * cols * sizeof(char *));
    char *data = (char *) (recipe_arr + rows);

    for (int i = 0; i < rows; ++i) {
        recipe_arr[i] = (char **) (data + i * cols * sizeof(char *));
        for (int j = 0; j < cols; ++j) {
            recipe_arr[i][j] = data + (rows * sizeof(char **) + i * cols + j) * sizeof(char);
        }
    }
    return recipe_arr;
}

void count_row_col(FILE *f, char *r_buffer, unsigned int *rows, unsigned int *col) {
    while (fgets(r_buffer, BUFFER, f)) {
        (*rows)++;
        char *recipe_string = strtok(r_buffer, ", \n");
        while (recipe_string != NULL) {
            (*col)++;
            recipe_string = strtok(NULL, ", \n");
        }
    }

}

char ***populate_array(FILE *file, char *recipe_buffer, char ***recipe_array) {
    int i = 0, j = 0;
    while (fgets(recipe_buffer, BUFFER, file)) {
        char *recipe_string = strtok(recipe_buffer, ", \n");
        while (recipe_string != NULL) {
            recipe_array[i][j] = (char *) malloc((strlen(recipe_string) + 1) * sizeof(char));
            strcpy(recipe_array[i][j], recipe_string);

            // Print the hole array, with all the recipes.
            //printf("%s ", recipe_array[i][j]);

            // Move to the next column
            ++j;

            // The next token is found.
            recipe_string = strtok(NULL, ", \n");
        }
        // Move to the next row
        printf("\n");
        ++i;

        // Reset column index
        j = 0;
    }
    return recipe_array;
}

// Function for finding missing ingredients.

