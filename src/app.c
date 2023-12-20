#include "library/app-library.c"
#include "library/load-library.c"
#include "library/compare-library.c"
#include "library/search-library.c"
#include <stdio.h>

int main() {
    // Open the text file for reading
    FILE *file = fopen("src/library/Recipe-library.txt", "r"); // load file into the location of the file pointer
    checkLoad(file);

    // User input variables
    int filteredCount = 0, uniqueCategoriesCount = 0, ingredientCount = 0, categoryCount = 0, choice;
    char uniqueCategories[MAX_CAT][MAX_NAME];
    char **categories = NULL;
    Ingredient *ingredients;
    Recipe *recipes = NULL; // Array to store recipe structs
    int recipeCount = loadRecipeStruct(file, &recipes, uniqueCategories, &uniqueCategoriesCount);

    // Step 1: Program Explanation
    printProgramExplanation();

    // Step 2: Get user input
    userInput(&ingredients, &ingredientCount, &categories, &categoryCount, recipes, recipeCount, uniqueCategories,
              uniqueCategoriesCount);


    // Step 3: Display dishes based on user input
    Recipe *filteredRecipes = filterRecipes(recipes, categories, categoryCount, recipeCount, &filteredCount);

    missingIngredientsAllRecipes(filteredRecipes, ingredients, ingredientCount);
    qsort(filteredRecipes, filteredCount, sizeof(Recipe), qsortCompare);

    fclose(file); // close the file

    // Step 4: Let the user pick their dish and choose the one to see
    choice = chooseRecipe(filteredRecipes);

    // Step 5: Search for missing ingredients and check where they can be bought cheapest
    char **missingIngredients = ingredientsNeeded(filteredRecipes[choice - 1], ingredientCount, ingredients);
    int length = filteredRecipes[choice - 1].missingIngredients;
    findLowestPrice(missingIngredients, length);

    // Free allocated memory for ingredients and categories
    if (ingredientCount != 0) {
        free(ingredients);
    }
    freeMemory(&categories, categoryCount);
    for (int i = 0; i < recipeCount; i++) {
        free(recipes[i].ingredients);
    }
    free(recipes);

    return 0;
}
