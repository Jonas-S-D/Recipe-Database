#include "library/app-library.c"
#include "library/load-library.c"
#include "library/compare-library.c"
#include "library/app-search.c"
#include <stdio.h>

int main() {
    // Open the text file for reading
    FILE *file = fopen("src/library/recipes.txt", "r"); // load file into the location of the file pointer
    checkLoad(file);

    // User input variables
    char uniqueCategories[MAX_CAT][MAX_NAME];
    int uniqueCategoriesCount = 0;
    Ingredient *ingredients;
    int ingredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;
    Recipe *recipes = NULL; // Array to store recipe structs
    int recipeCount = loadRecipeStruct(file, &recipes, uniqueCategories, &uniqueCategoriesCount);
    int filteredCount = 0;

    // Step 1: Program Explanation
    printProgramExplanation();

    // Step 2: Get user input
    userInput(&ingredients, &ingredientCount, &categories, &categoryCount, recipes, recipeCount, uniqueCategories, uniqueCategoriesCount);

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
