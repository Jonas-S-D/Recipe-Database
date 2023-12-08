/**
 * Compare function.
 * Look at compare flowchart (Figure 3.4) in Overleaf
*/

/**
 * The first two processes of the compare function receive the user's ingredients
 * and user categories as function input parameters from 'User Input',
 * the ingredients are needed when comparing the ingredients of a recipe with the user's ingredients.
 * The categories are needed to later limit the recipes being compared,
 * to recipes with the same category tags as the user wants,
 * if no category is selected by the user, then all recipes are going to be compared.
 */

// Receive ingredient input
void printIngredients(Ingredient *ingredients, int ingredientCount) {
    printf("Printing ingredients:\n");
    for (int i = 0; i < ingredientCount; ++i) {
        printf("Ingredient %d:\n", i + 1);
        printf("Name: %s\n", ingredients[i].name);
        printf("Amount: %lf\n", *ingredients[i].amount);
        // printf("Unit: %s\n", ingredients[i].unit);
        printf("\n");
    }
}

// Receive categories selected
void printCategories(char **categories, int categoryCount) {
    printf("Printing categories:\n");
    for (int i = 0; i < categoryCount; ++i) {
        printf("Category %d: %s\n", i + 1, categories[i]);
    }
}

/**
 * The process 'Receive Loaded Recipes' receives all recipes
 * as a function input parameter from the process 'Load recipe'
 */

// Receive loaded recipes
void printRecipe(Recipe recipe) {
    printf("\nPrinting recipe categories:\n");
    for (int i = 0; recipe.categories[i][0] != '\0'; ++i) {
        printf("Category of recipe %d: %s\n", i + 1, recipe.categories[i]);
    }
}

/**
 * The next process filters the loaded recipes if the user has entered one or more categories
 * then it removes all recipes with no matching category tag,
 * if the user hasn't entered any category, the filter process returns all recipes.
 */

// Filter loaded recipes by category
void filterRecipe(Recipe recipe, Recipe FilteredRecipe, char **categories, int CategoryCount) {
    for (int i = 0; recipe.categories[i][0] != '\0'; ++i) {
        for (int j = 0; j < CategoryCount; ++j) {
            if (&categories[i][0] != NULL) {
                if (strcmp(categories[i], recipe.categories[i]) == 0) {
                    FilteredRecipe = recipe;
                    printf("Test recipe category: %s\n", FilteredRecipe.categories[i]);
                }
            } else {
                printf("No category chosen\n");
            }
        }
    }


    /* for (int i = 0; i < CategoryCount; ++i) {
        for (int j = 0; recipe.categories[j][0] != '\0'; ++j) {
            if (strcmp(categories[i], recipe.categories[j]) == 0) {
                printf("\nTest succes\n");
                strcpy(FilteredRecipe.categories[i], recipe.categories[j]);
                strcpy(&FilteredRecipe.name[i], &recipe.name[j]);
                strcpy(&FilteredRecipe.explanation[i], &recipe.explanation[j]);
                strcpy(&FilteredRecipe.ingredients->name[i], &recipe.ingredients->name[j]);
                printf("Test recipe category: %s\n", FilteredRecipe.categories[i]);
                printf("Test recipe name: %s\n", &FilteredRecipe.name[i]);
                printf("Test recipe explanation: %s\n", &FilteredRecipe.explanation[i]);
                printf("Test recipe ingredients: %s\n", &FilteredRecipe.ingredients->name[i]);
            } else {
                printf("\nTest fail\n");
            }
        }
    } */
    /*for (int f = 0; f < 3; ++f) {
        // printf("Recipe 1 categories: %s\n", recipe.categories[f]);
        if (recipe.categories[f][0] != '\0') {
           printf("Recipe categories: %s\n", recipe.categories[f]);
        } else {
            printf("Empty\n");
        }
    }*/
    /*for (int b = 0; b < 1; ++b) {
        printf("Name: %s\n", &recipe.name[b]);
    }*/
}

void filterRecipes(Recipe *recipes, Recipe *FilteredRecipes, char **categories, int CategoryCount, int RecipeCount) {
    printf("Number of recipes tested: %d\n", RecipeCount);
    for (int i = 0; i < RecipeCount; i++) {
        printf("Printing test of recipe %d\n", i + 1);
        filterRecipe(recipes[i], FilteredRecipes[0], categories, CategoryCount);
    }
}

/**
 * The second last process of Compare 'Sort Recipes by least missing ingredients'
 * sorts recipes by comparing the user's stored ingredients with ingredients needed in each recipe,
 * and ordering the recipes from least missing ingredients to most missing ingredients.
 */

// Sort recipes by least missing ingredients


/**
 * The last process of Compare returns the three first recipes in the sorted list of recipes.
 */

// Return the first three recipes (the ones with the least missing ingredients)
