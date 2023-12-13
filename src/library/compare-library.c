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
    Recipe* FilteredRecipe = malloc(sizeof(Recipe) * 100);
    if (FilteredRecipe == NULL) {
        printf("Memory allocation failed for FilteredRecipe.\n");
        return NULL;
    }
    int counter = 0;

    if (categories != NULL && CategoryCount > 0) {
        for (int i = 0; i < CategoryCount; ++i) {
            for (int j = 0; recipe->categories[j][0] != '\0'; ++j) {
                if (strcmp(categories[i], recipe->categories[j]) == 0) {
                    int duplicate = 0;
                    for (int k = 0; k < counter; ++k) {
                        if (strcmp(FilteredRecipe[k].name, recipe->name) == 0) {
                            duplicate = 1;
                            break;
                        }
                    }

                    if (!duplicate) {
                            FilteredRecipe[counter] = *recipe;
                            counter++;
                        }
                    break; // Break from innermost for-loop
                } else {
                }
            }
        }
    } else { // No categories chosen
        FilteredRecipe[counter] = *recipe;
        counter++;
    }
    return FilteredRecipe;
}


Recipe* filterRecipes(const Recipe* recipes, char** categories, int CategoryCount, int RecipeCount, int *filteredCount) {
    // Check if the input parameters are valid
    if (recipes == NULL || RecipeCount <= 0) {
        printf("Invalid input parameters to filterRecipes.\n");
        return NULL;
    }

    Recipe* filteredRecipes = malloc(sizeof(Recipe) * RecipeCount);
    if (filteredRecipes == NULL) {
        printf("Memory allocation failed for filteredRecipes.\n");
        return NULL;
    }

    for (int i = 0; i < RecipeCount; i++) {
        Recipe* filtered = filterRecipe(&recipes[i], categories, CategoryCount);
        (*filteredCount)++;
        if (filtered == NULL) {
            printf("filterRecipe returned NULL for recipe %d (%s).\n", i, recipes[i].name);
        } else {
            filteredRecipes[i] = *filtered;
        }
    }
    filteredRecipes[RecipeCount].name[0] = '\0';

    for (int i = 0; i < RecipeCount; ++i) {
        if (filteredRecipes[i].name[0] == '\0') {
            for (int j = i; j < RecipeCount - 1; ++j) {
                filteredRecipes[j] = filteredRecipes[j + 1];
            }
            filteredRecipes[RecipeCount - 1].name[0] = '\0';
            RecipeCount--;
            (*filteredCount)--;
            --i;
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
    if (FilteredRecipes == NULL) {
        printf("FilteredRecipes is not accessible (NULL pointer).\n");
        return;
    }

    for (int i = 0; FilteredRecipes[i].name[0] != '\0'; ++i) {
        // Additional check (optional, based on your specific implementation)
        if (&FilteredRecipes[i] == NULL) {
            printf("FilteredRecipes[%d] is not accessible (NULL pointer).\n", i);
            continue; // Skip this iteration
        }

        printf("\n.... Checking: %s ....\n", FilteredRecipes[i].name);
        sortRecipes(&FilteredRecipes[i], ingredients, ingredientCount);
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
            if (strcmp(FilteredRecipe->ingredients[k].name, ingredients[j].name) == 0) {
                printf("Match found!\n");
                unitCompare(FilteredRecipe, ingredients, k, j);
                FilteredRecipe->missingIngredients--;
                break;
            }
        }
    }

    printf("\ningredientCount: %d\n", count);
    printf("missingCount: %d\n", FilteredRecipe->missingIngredients);
}

int unitCompare(Recipe* FilteredRecipe, Ingredient *ingredients, int recipe, int userInput) {
    double recipeAmount = FilteredRecipe->ingredients[recipe].amount[0];
    double userAmount = ingredients[userInput].amount[0];
    char recipeUnit[4];
    char userUnit[4];
    strcpy(recipeUnit, FilteredRecipe->ingredients[recipe].unit);
    strcpy(userUnit, ingredients[userInput].unit);

    unitConvert(recipeUnit, &recipeAmount);;
    unitConvert(userUnit, &userAmount);;

    printf("\n\nRecipe: %lf %s", recipeAmount, recipeUnit);
    printf("\nUser: %lf %s\n\n", userAmount, userUnit);

    if (strcmp(recipeUnit, userUnit) != 0) {
        return 0;
    } else if (recipeAmount > userAmount) {
        return 0;
    } else {
        return 1;
    }
}

void unitConvert(char *unit, double *amount) {
    if (strcmp(unit, "ml") == 0) {
        strcpy(unit, "dl");
        *amount /= 100;
    } else if (strcmp(unit, "l") == 0) {
        strcpy(unit, "dl");
        *amount *= 10;
    }
}

// Compare function
int compareFunction(const void *a, const void *b) {
    Recipe *recipeA = (Recipe *) a;
    Recipe *recipeB = (Recipe *) b;

    return (recipeA->missingIngredients - recipeB->missingIngredients);
}

// qsort
void qsortFunction(Recipe *FilteredRecipe, int size) {
    printf("Before sorting:\n");
    for (int i = 0; i < size; ++i) {
        printf("%s missing ingredients: %d\n", &FilteredRecipe[i].name[0], FilteredRecipe[i].missingIngredients);
    }

    qsort(FilteredRecipe, size, sizeof(Recipe), compareFunction);

    printf("After sorting:\n");
    for (int j = 0; j < size; ++j) {
        printf("%s missing ingredients: %d\n", FilteredRecipe[j].name, FilteredRecipe[j].missingIngredients);
    }
}


/**
 * The last process of Compare returns the three first recipes in the sorted list of recipes.
 */

// Return the first three recipes (the ones with the least missing ingredients)