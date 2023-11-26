// Created by Kristoffer Holm on 20/11/2023.
#include "compare-library.h"

int main() {

// Get stored and recipe arrays
    char **stored_arr = (char **) stored_to_array();
    char ***recipe_arr = (char ***) recipe_to_array();

    missing_ingredients(stored_arr, (char ***) recipe_arr);

    return 0;
}


