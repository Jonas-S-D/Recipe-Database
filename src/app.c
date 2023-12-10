#include "library/app-library.c"
#include "library/load-library.c"
#include <stdio.h>

// Test function der senere vil blive fjernet når vi ikke skal printe ingredienserne længere.
void printIngredients(Ingredient *ingredients, int ingredientCount) {
    printf("Printing ingredients:\n");
    for (int i = 0; i < ingredientCount; ++i) {
        printf("Ingredient %d:\n", i + 1);
        printf("Name: %s\n", ingredients[i].name);
        printf("Amount: %.2lf ", *ingredients[i].amount);
        printf("\nUnit: %s\n", ingredients[i].unit);
        printf("\n");
    }
}

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

    // Step 1: Program Explanation
    // printProgramExplanation();

    // Step 2: Get user input
    userInput(&ingredients, &ingredientCount, &categories, &categoryCount);
    // Test functionen der printer ingredienserne.
    printIngredients(ingredients, ingredientCount);

    // Step 3: Display dishes based on user input
    /*
    print_recipes(recipes, recipeCount);
    fclose(file); // close the file
    printf("testing -> %s",recipes[0].name);
    */

    // Step 4: Let the user pick their dish

    // Step 5: Display the recipe.


    // Free allocated memory for ingredients and categories
    free(ingredients);
    freeMemory(&categories, categoryCount);
    for (int i = 0; i < recipeCount; i++) {
        free(recipes[i].ingredients);
    }
    free(recipes);

    return 0;
}

