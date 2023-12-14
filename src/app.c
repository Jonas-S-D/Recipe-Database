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
    char **category_array;
    int ingredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;
    Recipe *recipes = NULL; // Array to store recipe structs
    int recipeCount = load_recipe_struct(file, &recipes, unique_categories, &unique_categories_count);
    int filteredCount = 0;

    // Step 1: Program Explanation
    // printProgramExplanation();

    for (int i = 0; i < unique_categories_count; i++) {
        printf("%s\n", unique_categories[i]);
    }

    // Step 2: Get user input
    userInput(&ingredients, &ingredientCount, &categories, &categoryCount, recipes, recipeCount, unique_categories);

    for (int i = 0; i < categoryCount; i++) {
        printf("%s\n", categories[i]);
    }
    // Step 3: Display dishes based on user input
    Recipe *filteredRecipes = filterRecipes(recipes, categories, categoryCount, recipeCount, &filteredCount);

    if (filteredRecipes == NULL) {
        printf("filterRecipes returned a NULL pointer. Check for errors inside the function.\n");
    }

    sortFilteredRecipes(filteredRecipes, ingredients, ingredientCount);

    qsortFunction(filteredRecipes, filteredCount);
    // sortRecipes(FilteredRecipe, *ingredients);

    // print_recipes(recipes, recipeCount);
    fclose(file); // close the file
    // printf("testing -> %s",recipes[0].name);

    // Step 4: Let the user pick their dish

    // Step 5: Display the recipe.


    // Free allocated memory for ingredients and categories

    // free(ingredients);
    // freeMemory(&categories, categoryCount);
    // for (int i = 0; i < recipeCount; i++) {
    //     free(recipes[i].ingredients);
    // }
    //
  
    free(recipes);

    return 0;
}
