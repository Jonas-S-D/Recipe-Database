#include "library/app-library.c"
#include "Compare ingredients/compare-library.c"
#include <stdio.h>

int main() {
    // User input variables
    char **userIngredients = NULL;
    int userIngredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;

    // Step 1: Program Explanation

    // Step 2: Get user input
    getUserInput(&userIngredients, &userIngredientCount, &categories, &categoryCount);

    // Step 3: Display dishes based on user input

    // Step 4: Let the user pick their dish

    // Step 5: Display the recipe.

    // Free allocated memory for ingredients and categories
    freeMemory(&userIngredients, userIngredientCount);
    freeMemory(&categories, categoryCount);

    return 0;
}