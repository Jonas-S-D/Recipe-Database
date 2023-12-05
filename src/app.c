#include "library/app-library.c"
#include "Compare/compare-library.c"
#include <stdio.h>

int main() {
    // User input variables
    struct Ingredient *ingredients;
    int ingredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;

    // Step 1: Program Explanation
    printProgramExplanation();

    // Step 2: Get user input
    getUserInput(&ingredients, &ingredientCount, &categories, &categoryCount);

    // Step 3: Display dishes based on user input

    // Step 4: Let the user pick their dish

    // Step 5: Display the recipe.

    // Free allocated memory for ingredients and categories
    free(ingredients);
    freeMemory(&categories, categoryCount);

    return 0;
}