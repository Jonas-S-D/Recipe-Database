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
Recipe* filterRecipe(const Recipe* recipe, char** categories, int CategoryCount) {
    Recipe* FilteredRecipe = malloc(sizeof(Recipe));

    if (FilteredRecipe != NULL) {
        int counter = 0;

        if (categories != NULL) {
            for (int i = 0; i < CategoryCount; ++i) {
                for (int j = 0; recipe->categories[j][0] != '\0'; ++j) {
                    if (strcmp(categories[i], recipe->categories[j]) == 0) {
                        int duplicate = 0;
                        for (int k = 0; k < counter; ++k) {
                            if (strcmp(FilteredRecipe->name, recipe->name) == 0) {
                                duplicate = 1;
                                break;
                            }
                        }

                        if (!duplicate) {
                            *FilteredRecipe = *recipe;
                            counter++;
                        }
                        break;
                    }
                }
            }
        } else { // No categories chosen
            *FilteredRecipe = *recipe;
        }
    }

    return FilteredRecipe;
}

Recipe* filterRecipes(const Recipe* recipes, char** categories, int CategoryCount, int RecipeCount) {
    Recipe* filteredRecipes = malloc(sizeof(Recipe) * RecipeCount);

    if (filteredRecipes != NULL) {
        for (int i = 0; i < RecipeCount; i++) {
            filteredRecipes[i] = *filterRecipe(&recipes[i], categories, CategoryCount);
        }
    }

    return filteredRecipes;
}

/**
 * The second last process of Compare 'Sort Recipes by least missing ingredients'
 * sorts recipes by comparing the user's stored ingredients with ingredients needed in each recipe,
 * and ordering the recipes from least missing ingredients to most missing ingredients.
 */

void sortFilteredRecipes(Recipe* FilteredRecipes, Ingredient* ingredients, int ingredientCount) {
    for (int i = 0; FilteredRecipes[i].name[0] != '\0'; ++i) {
        printf("\n.... Checking: %s ....\n", FilteredRecipes[i].name);
        sortRecipes(&FilteredRecipes[i], ingredients, ingredientCount);  // Pass a pointer
    }
}

// Sort recipes by least missing ingredients
void sortRecipes(Recipe* FilteredRecipe, Ingredient* ingredients, int ingredientCount) {
    int count = 0;

    for (int i = 0; FilteredRecipe->ingredients[i].name[0] != '\0'; ++i) {
        count++;
    }
    FilteredRecipe->missingIngredients = count;

    for (int j = 0; j < ingredientCount; ++j) {
        printf("\nChecking ingredient: %s\n", ingredients[j].name);
        for (int k = 0; FilteredRecipe->ingredients[k].name[0] != '\0'; ++k) {
            printf("Comparing with: %s\n", FilteredRecipe->ingredients[k].name);

            // Defensive check to avoid invalid memory access
            if (k >= MAX_AMOUNT || j >= MAX_AMOUNT) {
                printf("Invalid index detected! Aborting...\n");
                return;
            }

            if (strcmp(FilteredRecipe->ingredients[k].name, ingredients[j].name) == 0) {
                printf("Match found!\n");
                FilteredRecipe->missingIngredients--;
                break;
            }
        }
    }

    printf("\ningredientCount: %d\n", count);
    printf("missingCount: %d\n", FilteredRecipe->missingIngredients);
}

/**
 * The last process of Compare returns the three first recipes in the sorted list of recipes.
 */

// Return the first three recipes (the ones with the least missing ingredients)