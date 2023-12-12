#include "library/app-library.c"
#include "library/load-library.c"
#include "library/compare-library.c"
#include <stdio.h>

int main() {
    // Open the text file for reading
    FILE *file = fopen("src/library/recipes.txt", "r"); // load file into the location of the file pointer
    check_load(file);

    // User input variables
    Ingredient *ingredients;
    int ingredientCount = 0;
    char **categories = NULL;
    int categoryCount = 0;
    Recipe *recipes = NULL; // Array to store recipe structs
    int recipeCount = load_recipe_struct(file, &recipes);
    Recipe FilteredRecipe;

    // Step 1: Program Explanation
    // printProgramExplanation();

    // Step 2: Get user input
// Initial setup if needed
// Initialize ingredientCount and categoryCount
    ingredientCount = 0;
    categoryCount = 0;
// Allocate memory for ingredients and categories if they are dynamically allocated

    userInput(&ingredients, &ingredientCount, &categories, &categoryCount);

// Debug prints after the function call
    printf("After userInput call:\n");
    printf("Ingredient Count: %d\n", ingredientCount);
    printf("Category Count: %d\n", categoryCount);

// If ingredients and categories are arrays, you might want to iterate through them and print their contents
    for (int i = 0; i < ingredientCount; ++i) {
        printf("Ingredient %d: %s\n", i, ingredients[i].name); // Modify as per your Ingredient structure
    }

    for (int i = 0; i < categoryCount; ++i) {
        printf("Category %d: %s\n", i, categories[i]); // Modify as per your data type for categories
    }

    printf("Checking recipes array:\n");
    for (int i = 0; i < recipeCount; ++i) {
        // recipe 0:
        printf("Recipe %d: %s\n", i, recipes[i].name);
        // Add more details if needed
    }


    // Step 3: Display dishes based on user input
    Recipe *filteredRecipes = filterRecipes(recipes, categories, categoryCount, recipeCount);

// 1. Check if the returned pointer is valid
    if (filteredRecipes == NULL) {
        printf("filterRecipes returned a NULL pointer. Check for errors inside the function.\n");
    } else {
        printf("filterRecipes returned a valid pointer. Proceeding to check contents.\n");

        // 2. (Optional) Print some details of the returned array for verification
        for (int i = 0; filteredRecipes[i].name[0] != '\0'; ++i) {
            printf("Filtered Recipe %d: %s\n", i, filteredRecipes[i].name);
            // Add more details if needed
        }
    }




    sortFilteredRecipes(filteredRecipes, ingredients, ingredientCount);
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
