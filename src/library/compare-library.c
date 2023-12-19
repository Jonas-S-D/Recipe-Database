/**
 * Filters a recipe by user categories.
 * @param recipe All recipes
 * @param categories User chosen categories
 * @param categoryCount Amount of user chosen categories
 * @return Returns the filteres recipes, in a Recipe struct.
 */
Recipe *filterRecipe(const Recipe *recipe, char **categories, int categoryCount) {
    Recipe *filteredRecipe = NULL; // Initialize to NULL

    if (categories != NULL && categoryCount > 0) { // At least one category chosen
        for (int i = 0; i < categoryCount; ++i) { // Checks through the user's categories
            if (recipeHasCategory(recipe, categories[i])) {
                // Allocate memory for filteredRecipe only if a category is found
                if (filteredRecipe == NULL) {
                    filteredRecipe = malloc(sizeof(Recipe));
                    if (filteredRecipe == NULL) {
                        printf("Memory allocation failed for 'filteredRecipe'. Exiting program...\n");
                        exit(EXIT_FAILURE);
                    }
                    *filteredRecipe = *recipe;
                }
            }
        }
    } else { // No categories chosen
        filteredRecipe = malloc(sizeof(Recipe));
        if (filteredRecipe == NULL) {
            printf("Memory allocation failed for 'filteredRecipe'. Exiting program...\n");
            exit(EXIT_FAILURE);
        }
        *filteredRecipe = *recipe;
    }

    return filteredRecipe;
}

/**
 * Checks if a recipe has a specific category.
 * @param recipe Pointer to the recipe to check.
 * @param category The category to check for in the recipe.
 * @return 1 if the category is found in the recipe's categories, 0 otherwise.
 */
// Check if the recipe has a specific category
int recipeHasCategory(const Recipe *recipe, const char *category) {
    for (int j = 0; recipe->categories[j][0] != '\0'; ++j) { // Checks through the recipe's categories
        if (strcmp(category, recipe->categories[j]) == 0) {
            return 1; // Category found
        }
    }
    return 0; // Category not found
}

/**
 * Filters recipes based on specified categories.
 * @param recipes An array of all recipes.
 * @param categories An array of user-chosen categories.
 * @param categoryCount The number of user-chosen categories.
 * @param recipeCount The total number of recipes in the 'recipes' array.
 * @param filteredCount A pointer to an integer that will be updated with the count of filtered recipes.
 * @return An array of filtered recipes matching the user-input categories.
 */
Recipe *filterRecipes(const Recipe *recipes, char **categories, int categoryCount, int recipeCount, int *filteredCount) {
    if (recipes == NULL || recipeCount <= 0) { // Check if the input parameters are valid
        printf("Invalid input parameter 'filterRecipes'.\n");
        return NULL;
    }

    Recipe *filteredRecipes = malloc(sizeof(Recipe) * recipeCount);
    if (filteredRecipes == NULL) {
        printf("Memory allocation failed for 'filteredRecipes'. Exiting program...\n");
        exit(EXIT_FAILURE);
    }

    *filteredCount = 0;

    // Filters the number of recipes using the filterRecipes function
    for (int i = 0; i < recipeCount; i++) {
        Recipe *filtered = filterRecipe(&recipes[i], categories, categoryCount);
        if (filtered != NULL) {
            filteredRecipes[*filteredCount] = *filtered;
            (*filteredCount)++;
            free(filtered); // Free memory allocated in filterRecipe
        }
    }

    // Resize the array to match the number of filtered recipes
    filteredRecipes = realloc(filteredRecipes, sizeof(Recipe) * (*filteredCount));

    printf("\n");

    return filteredRecipes;
}

/**
 * Sorts the list of filtered recipes, in order from least to most missing ingredients.
 * @param filteredRecipes List of filtered recipes.
 * @param ingredients Users inventory of ingredients.
 * @param ingredientCount The amount of ingredients, that the user has.
 */
void missingIngredientsAllRecipes(Recipe *filteredRecipes, Ingredient *ingredients, int ingredientCount) {
    if (filteredRecipes == NULL) {
        printf("'filteredRecipes' er ikke tilgaengelige (NULL pointer).\n");
        return;
    }

    for (int i = 0; filteredRecipes[i].name[0] != '\0'; ++i) {
        // Additional check (optional, based on your specific implementation)
        if (&filteredRecipes[i] == NULL) {
            printf("'FilteredRecipes[%d]' er ikke tilgaengelig (NULL pointer).\n", i);
            continue; // Skip this iteration
        }
        countMissingIngredients(&filteredRecipes[i], ingredients, ingredientCount);
    }
}


/**
 * Auxiliary function to missingIngredientsAllRecipes, which counts the number of missing ingredients for a recipe.
 * @param filteredRecipe All filtered recipes.
 * @param ingredients All the users ingredients.
 * @param ingredientCount The amount of ingredients that the user has.
 */
void countMissingIngredients(Recipe *filteredRecipe, Ingredient *ingredients, int ingredientCount) {
    int count = 0;

    // Finds the number of ingredients, in the index i number of  filteredRecipe.
    for (int i = 0; filteredRecipe->ingredients[i].name[0] != '\0'; ++i) {
        count++;
    }

    // Compares the all the ingredients from the user input, with all the ingredients in filteredRecipe.
    for (int j = 0; j < ingredientCount; ++j) {
        for (int k = 0; filteredRecipe->ingredients[k].name[0] != '\0'; ++k) {
            if (strcmp(filteredRecipe->ingredients[k].name, ingredients[j].name) == 0) {
                if (unitCompare(filteredRecipe, ingredients, k, j) == 1) {
                    count--;
                    break;
                }
                break;
            }
        }
    }
    filteredRecipe->missingIngredients = count;
}

/**
 * Compares different units.
  * @param filteredRecipe The filtered recipe being tested.
 * @param ingredients All ingredients entered by the user.
 * @param recipe The index of the filtered recipe's ingredient being tested.
 * @param userInput The index of a user ingredient being compared.
 * @return Returns 1 if the user has enough of that ingredient and the unit matches, 0 otherwise.
 */
int unitCompare(Recipe *filteredRecipe, Ingredient *ingredients, int recipe, int userInput) {
    double recipeAmount = filteredRecipe->ingredients[recipe].amount[0];
    double userAmount = ingredients[userInput].amount[0];
    char recipeUnit[4];
    char userUnit[4];
    strcpy(recipeUnit, filteredRecipe->ingredients[recipe].unit);
    strcpy(userUnit, ingredients[userInput].unit);

    unitConvert(recipeUnit, &recipeAmount);;
    unitConvert(userUnit, &userAmount);;

    if (strcmp(recipeUnit, userUnit) != 0) {
        return 0;
    } else if (recipeAmount > userAmount) {
        return 0;
    } else {
        return 1;
    }
}

/**
 * Converts different units.
 * @param unit Pointer to the user input of unit to be converted.
 * @param amount Pointer to the user input of amount corresponding to the unit.
 */
void unitConvert(char *unit, double *amount) {
    if (strcmp(unit, "ml") == 0) {
        strcpy(unit, "dl");
        *amount /= 100;
    } else if (strcmp(unit, "l") == 0) {
        strcpy(unit, "dl");
        *amount *= 10;
    } else if (strcmp(unit, "kg") == 0) {
        strcpy(unit, "g");
        *amount *= 1000;
    }
}
/**Auxiliary function for qsort
 * @param a Pointer to the first recipe
 * @param b Pointer to the second recipe
* @return Negative value if recipe A has fewer missing ingredients than recipe B,
 *         0 if both recipes have the same number of missing ingredients,
 *         Positive value if recipe A has more missing ingredients than recipe B.
 */
int qsortCompare(const void *a, const void *b) {
    Recipe *recipeA = (Recipe *) a;
    Recipe *recipeB = (Recipe *) b;

    return (recipeA->missingIngredients - recipeB->missingIngredients);
}

/**
 * Find the lowest price of all missingIngredients, and finds the store in which it can be bought.
 * @param missingIngredients An array of missing ingredients, of the chosen recipe.
 * @param arrLength The length of the missingIngredients array.
 */
void findLowestPrice(char **missingIngredients, int arrLength) {
    /* opens file and returns an error if file pointer points to NULL */
    FILE *file = fopen("src/library/prices.txt", "r");
    if (file == NULL) {
        printf("Fejl ved at aabne prices.txt filen\n");
        return;
    }

    Item *ingredients;
    char buffer[MAX_LINE];
    int structLength = 0;

    /* counts number of rows in file */
    while (!feof(file)) {
        fgets(buffer, MAX_LINE, file);
        structLength++;
    }
    /* resets file pointer position to beginning of file */
    fseek(file, 0, SEEK_SET);

    /* allocates memory for array of structs depending on number of rows in csv file */
    ingredients = malloc(structLength * sizeof(Item));
    if (ingredients == NULL) {
        printf("Hukommelses allokeringen fejlede\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    /* scans data from file into array of structs */
    int count = 0;
    while (!feof(file)) {
        fscanf(file, "%[^,], %[^,], %[^,],%lf,\n", ingredients[count].store, ingredients[count].unit,
               ingredients[count].name, &ingredients[count].price);
        count++;
    }
    fclose(file);

    /* variables used to save each ingredient, the lowest price and the store which it can be bought */
    char storeName[MAX_NAME];
    char itemName[MAX_NAME];
    char units[MAX_NAME];
    double lowestPrice = 1000;
    printf("\nManglende ingredienser er:\n");

    /* searches for which store has the lowest price for each ingredient */
    for (int i = 0; i < arrLength; i++) {
        lowestPrice = 1000;
        for (int j = 0; j < structLength; j++) {
            if (strcmp(missingIngredients[i], ingredients[j].name) == 0 && lowestPrice > ingredients[j].price) {
                lowestPrice = ingredients[j].price;
                strcpy(storeName, ingredients[j].store);
                strcpy(itemName, ingredients[j].name);
                strcpy(units, ingredients[j].unit);
            }
        }
        /* checks if ingredient was found in the struct array */
        if (strcmp(missingIngredients[i], itemName) == 0) {
            printf("%s %s kan kobes billigst i %s for %.2lf kr.\n", units, itemName, storeName, lowestPrice);
        } else {
            printf("%s findes ikke i databasen\n", missingIngredients[i]);
        }
    }

    /* free memory allocated */
    for (int i = 0; i < arrLength; i++) {
        free(missingIngredients[i]);
    }
    free(missingIngredients);
    free(ingredients);
}

/**
 * Makes an array of missing ingredients, in the chosen recipe.
 * @param userChosenRecipe The recipe that the user has chosen
 * @param userIngredients The amount of ingredients which the user has entered
 * @param ingredients All ingredients that the user has entered.
 * @returns Missing ingredients.
 */
char **ingredientsNeeded(Recipe userChosenRecipe, int userIngredients, Ingredient *ingredients) {
    /* counts the number of ingredients in the recipe chosen by the user */
    int recipeIngredients = 0;
    for (int j = 0; userChosenRecipe.ingredients[j].name[0] != '\0'; j++) {
        recipeIngredients++;
    }

    /* dynamically allocates memory for array of strings which will contain name of each missing ingredient in recipe */
    int arrLength = userChosenRecipe.missingIngredients;
    char **missingIngredients = malloc(sizeof(char *) * arrLength);

    int index = 0;
    int commonIngredients;

    /* runs through each ingredient from the recipe */
    for (int i = 0; i < recipeIngredients; i++) {
        commonIngredients = 0;
        /* runs through each ingredient entered by the user */
        for (int j = 0; j < userIngredients; j++) {
            /* checks for common ingredients */
            if (strcmp(userChosenRecipe.ingredients[i].name, ingredients[j].name) == 0 &&
                ingredients[j].amount[0] >= userChosenRecipe.ingredients[i].amount[0]) {
                commonIngredients++;
            }
        }
        /* if the nested loop didn't find an ingredient in the recipe that corresponds to the ones entered by the user then add ingredient to array */
        if (commonIngredients < 1) {
            missingIngredients[index] = malloc(strlen(ingredients[i].name) + 1);
            strcpy(missingIngredients[index], userChosenRecipe.ingredients[i].name);
            index++;
        }
    }
    // Allocated memory for missingIngredients is being freed in the findLowestPrice function
    return missingIngredients;
}