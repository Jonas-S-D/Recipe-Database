#include "library/app-library.c"
#include "library/load-library.c"
#include "library/compare-library.c"
#include "library/app-search.c"
#include <stdio.h>

// Test function der senere vil blive fjernet når vi ikke skal printe ingredienserne længere.
void printIngredients(Ingredient *ingredients, int ingredientCount) {
    printf("Printing ingredients:\n");
    for (int i = 0; i < ingredientCount; ++i) {
        printf("Ingredient %d:\n", i + 1);
        printf("Name: %s\n", ingredients[i].name);
        printf("Amount: %.2lf\n", *ingredients[i].amount);
        printf("Unit: %s\n", ingredients[i].unit);
        printf("\n");
    }
}

int main() {
    // Open the text file for reading
    FILE *file = fopen("src/library/recipes.txt", "r"); // load file into the location of the file pointer
    check_load(file);

    // User input variables
    char unique_categories[MAX_CAT][MAX_NAME];
    int unique_categories_count = 0;
    Ingredient *ingredients;
    int ingredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;
    Recipe *recipes = NULL; // Array to store recipe structs
    int recipeCount = load_recipe_struct(file, &recipes, unique_categories, &unique_categories_count);
    int filteredCount = 0;

    // Step 1: Program Explanation
    printProgramExplanation();

    // Step 2: Get user input
    userInput(&ingredients, &ingredientCount, &categories, &categoryCount, recipes, recipeCount, unique_categories, unique_categories_count);

    // Step 3: Display dishes based on user input
    Recipe *filteredRecipes = filterRecipes(recipes, categories, categoryCount, recipeCount, &filteredCount);
    if (filteredRecipes == NULL) {
        printf("filterRecipes returned a NULL pointer. Check for errors inside the function.\n");
    }
    sortFilteredRecipes(filteredRecipes, ingredients, ingredientCount);
    qsort(filteredRecipes, filteredCount, sizeof(Recipe), compareFunction);

    fclose(file); // close the file

    // Step 4: Let the user pick their dish and choose the one to see
    chooseRecipe(filteredRecipes);


    // Free allocated memory for ingredients and categories
    free(ingredients);
    freeMemory(&categories, categoryCount);
    for (int i = 0; i < recipeCount; i++) {
        free(recipes[i].ingredients);
     }
    free(recipes);

    return 0;
}
