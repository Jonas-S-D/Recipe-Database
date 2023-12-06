#include "compare-library.h"

FILE *open_file(char *file, char *mode) {
    FILE *f = fopen(file, mode);
    if (!f) {
        perror(file);
        exit(EXIT_FAILURE);
    } else return f;
}

unsigned int file_length(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    return length;
}

char *stored_to_array() {
    char stored_buffer[FILE_BUFFER];
    // Opens the file and check if the file opens.
    FILE *stored = open_file("src/Compare/CSV/Stored.csv", "r");

    // Counts the number of characters in the file.
    unsigned int length = file_length(stored);

    // Allocates an array with the length of the csv file.
    char **stored_arr = (char **) malloc((length + 1) * sizeof(char *));
    int i = 0;
    //printf("Ingredients: ");
    while (fgets(stored_buffer, FILE_BUFFER, stored)) {
        char *stored_string = strtok(stored_buffer, ", \n");

        while (stored_string != NULL) {
            stored_arr[i] = (char *) malloc((strlen(stored_string) + 1) * sizeof(char));
            strcpy(stored_arr[i], stored_string);

            //printf("%s ", stored_arr[i]);

            stored_string = strtok(NULL, ", \n");
            ++i;
        }
    }
    //printf("\n\n");
    fclose(stored);
    return (char *) stored_arr;
}

char ***recipe_to_array() {
    char recipe_buffer[FILE_BUFFER];

    // Opens the file and check if it opens
    FILE *recipe = open_file("src/Compare/CSV/Recipe.csv", "r");

    // Count the number of rows and columns
    unsigned int num_rows = 0, num_cols = 0;
    count_row_col(recipe, recipe_buffer, &num_rows, &num_cols);
    printf("row %d \ncol %d\n\n", num_rows, num_cols);

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
    // Allocate memory for the array of pointers to rows
    char ***recipe_arr = (char ***) malloc(rows * sizeof(char **));

    // Allocate memory for the data and initialize pointers
    char *data = (char *) malloc((rows * cols) * sizeof(char));
    for (int i = 0; i < rows; ++i) {
        recipe_arr[i] = (char **) malloc(cols * sizeof(char *));
        for (int j = 0; j < cols; ++j) {
            // Calculate the index into the 1D data array
            unsigned int index = i * cols + j;
            // Set the pointer to the corresponding location in the data array
            recipe_arr[i][j] = data + index;
        }
    }

    return recipe_arr;
}

void count_row_col(FILE *f, char *r_buffer, unsigned int *rows, unsigned int *col) {
    while (fgets(r_buffer, FILE_BUFFER, f)) {
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
    //printf("Recipes:\n");
    while (fgets(recipe_buffer, FILE_BUFFER, file)) {
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
        //printf("\n");
        ++i;

        // Reset column index
        j = 0;
    }

    return recipe_array;
}


// Function for finding missing ingredients.
void missing_ingredients(char **stored_array, char ***recipe_array) {
    for (int c = 0; c < NUM_RECIPES; ++c) {
        int stored_length = 0, common = 0, missing = 0;

        while (stored_array[stored_length] != NULL) {
            stored_length++;
        }

        for (int i = 1; i <= RECIPE_MAX_INGREDIENTS; ++i) {
            int j;
            for (j = 0; j < stored_length; ++j) {
                if (strncmp(recipe_array[c][i], "", 1) == 0) {
                    break;
                } else if (strcmp(recipe_array[c][i], stored_array[j]) == 0) {
                    common++;
                    break;
                }
            }

            if (j == stored_length) {
                missing++;
            }
        }

        print_missing(recipe_array, c, common, missing);
    }
}

void print_missing(char ***recipe_array, int c, int common, int missing) {
    printf("For %s:\nThere are %d common ingredients\nThere are %d missing ingredients\n\n", recipe_array[c][0], common,
           missing);
}