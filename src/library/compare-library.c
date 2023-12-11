/**
 * Compare function.
 * Look at compare flowchart (Figure 3.4) in Overleaf
*/

/**
 * The next process filters the loaded recipes if the user has entered one or more categories
 * then it removes all recipes with no matching category tag,
 * if the user hasn't entered any category, the filter process returns all recipes.
 */

// Filter loaded recipes by category
void filterRecipe(Recipe recipe, Recipe FilteredRecipe, char **categories, int CategoryCount, int recipeCount) {
    int counter = 0;
    if (categories != NULL) {
        for (int i = 0; i < CategoryCount; ++i) { // Number of chosen categories
            for (int j = 0; recipe.categories[j][0] != '\0'; ++j) { // Number of all categories
                if (strcmp(categories[i], recipe.categories[j]) == 0) {
                    int duplicate = 0;
                    for (int k = 0; k < counter; ++k) {
                        if (strcmp(FilteredRecipe.name, recipe.name) == 0) {
                            duplicate = 1;
                            break;
                        }
                    }
                    if (!duplicate) {
                        memcpy(&FilteredRecipe, &recipe, sizeof(recipe)); // Undersøg hvordan den virker her
                        counter++;
                    }
                    break;
                }
            }
        }
    } else { // No categories chosen
        memcpy(&FilteredRecipe, &recipe, sizeof(recipe));
    }
}

void filterRecipes(Recipe *recipes, Recipe *FilteredRecipes, char **categories, int CategoryCount, int RecipeCount) {
    // printf("Number of recipes tested: %d\n", RecipeCount);
    for (int i = 0; i < RecipeCount; i++) {
        // printf("Printing test of recipe %d\n", i + 1);
        filterRecipe(recipes[i], FilteredRecipes[0], categories, CategoryCount, RecipeCount);
    }
}

/**
 * The second last process of Compare 'Sort Recipes by least missing ingredients'
 * sorts recipes by comparing the user's stored ingredients with ingredients needed in each recipe,
 * and ordering the recipes from least missing ingredients to most missing ingredients.
 */

// Sort recipes by least missing ingredients
void sortRecipes(Recipe FilteredRecipe, Ingredient ingredients) {
    int ingredientCount = 0;
    int missingCount = 0;
    for (int i = 0; FilteredRecipe.ingredients->name[i] != '\0'; ++i) {
        ingredientCount++;
    }
    while (ingredients.name[0] != '\0') {
        for (int j = 0; FilteredRecipe.ingredients->name[j]; ++j) {
            for (int k = 0; ingredients.name[k]; ++k) {
                if (strcmp(&ingredients.name[j], &ingredients.name[k]) != 0) {
                    missingCount++;
                }
            }
        }
    }
    printf("ingredientCount: %d", ingredientCount);
    printf("missingCount: %d", missingCount);
}

/**
 * The last process of Compare returns the three first recipes in the sorted list of recipes.
 */

// Return the first three recipes (the ones with the least missing ingredients)
