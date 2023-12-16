// Filter loaded recipes by category
Recipe *filterRecipe(const Recipe *recipe, char **categories, int categoryCount) {
    Recipe *filteredRecipe = malloc(sizeof(Recipe)); // Dynamically allocates FilteredRecipe
    if (filteredRecipe == NULL) {
        printf("Memory allocation failed for FilteredRecipe.\n");
        return NULL;
    }

    if (categories != NULL && categoryCount > 0) { // At least one category chosen
        for (int i = 0; i < categoryCount; ++i) { // Checks through the users categories
            filterRecipeCategories(recipe, categories, filteredRecipe, i);
        }
    } else { // No categories chosen
        *filteredRecipe = *recipe;
    }

    return filteredRecipe;
}

// Filter the recipes' categories for 'filterRecipe'
void filterRecipeCategories(const Recipe *recipe, char **categories, Recipe *filteredRecipe, int i) {
    for (int j = 0; recipe->categories[j][0] != '\0'; ++j) { // Checks through the recipes categories
        if (strcmp(categories[i], recipe->categories[j]) == 0) {
            *filteredRecipe = *recipe;
            break;
        }
    }
}

Recipe *filterRecipes(const Recipe *recipes, char **categories, int categoryCount, int recipeCount, int *filteredCount) {
    if (recipes == NULL || recipeCount <= 0) { // Check if the input parameters are valid
        printf("Invalid input parameters to filterRecipes.\n");
        return NULL;
    }

    Recipe *filteredRecipes = malloc(sizeof(Recipe) * recipeCount);
    if (filteredRecipes == NULL) {
        printf("Memory allocation failed for filteredRecipes.\n");
        return NULL;
    }

    for (int i = 0; i < recipeCount; i++) {
        Recipe *filtered = filterRecipe(&recipes[i], categories, categoryCount);
        (*filteredCount)++;
        if (filtered == NULL) {
            printf("filterRecipe returned NULL for recipe %d (%s).\n", i, recipes[i].name);
        } else {
            filteredRecipes[i] = *filtered;
        }
    }
    filteredRecipes[recipeCount].name[0] = '\0';

    for (int i = 0; i < recipeCount; ++i) {
        if (filteredRecipes[i].name[0] == '\0') {
            for (int j = i; j < recipeCount - 1; ++j) {
                filteredRecipes[j] = filteredRecipes[j + 1];
            }
            filteredRecipes[recipeCount - 1].name[0] = '\0';
            recipeCount--;
            (*filteredCount)--;
            --i;
        }
    }

    return filteredRecipes;
}

void sortFilteredRecipes(Recipe *filteredRecipes, Ingredient *ingredients, int ingredientCount) {
    if (filteredRecipes == NULL) {
        printf("filteredRecipes is not accessible (NULL pointer).\n");
        return;
    }

    for (int i = 0; filteredRecipes[i].name[0] != '\0'; ++i) {
        // Additional check (optional, based on your specific implementation)
        if (&filteredRecipes[i] == NULL) {
            printf("FilteredRecipes[%d] is not accessible (NULL pointer).\n", i);
            continue; // Skip this iteration
        }
        sortRecipes(&filteredRecipes[i], ingredients, ingredientCount);
    }
}


// Sort recipes by least missing ingredients
void sortRecipes(Recipe *filteredRecipe, Ingredient *ingredients, int ingredientCount) {
    int count = 0;

    for (int i = 0; filteredRecipe->ingredients[i].name[0] != '\0'; ++i) {
        count++;
    }

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

// Compare function
int compareFunction(const void *a, const void *b) {
    Recipe *recipeA = (Recipe *) a;
    Recipe *recipeB = (Recipe *) b;

    return (recipeA->missingIngredients - recipeB->missingIngredients);
}

// Finds which store that has the lowest price of an ingredient
void findLowestPrice(char **missingIngredients, int arrLength) {
    /* opens file and returns an error if file pointer points to NULL */
    FILE *file = fopen("src/library/prices.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
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
        printf("Failed to allocate memory\n");
        fclose(file);
        return;
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
    for (int i = 0; i < arrLength; i++)
    {
        free(missingIngredients[i]);
    }
    free(missingIngredients);
    free(ingredients);
}

/* creates an array of the missing ingredients needed to complete a recipe */
char **ingredientsNeeded(Recipe filteredRecipes, int userIngredients, Ingredient *ingredients)
{
    /* counts the number of ingredients in the recipe chosen by the user */
    int recipeIngredients = 0;
    for (int j = 0; filteredRecipes.ingredients[j].name[0] != '\0'; j++)
    {
        recipeIngredients++;
    }

    /* dynamically allocates memory for array of strings which will contain name of each missing ingredient in recipe */
    int arrLength = filteredRecipes.missingIngredients;
    char **missingIngredients = malloc(sizeof(char *) * arrLength);

    int index = 0;
    int commonIngredients;

    /* runs through each ingredient from the recipe */
    for (int i = 0; i < recipeIngredients; i++)
    {
        commonIngredients = 0;
        /* runs through each ingredient entered by the user */
        for (int j = 0; j < userIngredients; j++)
        {
            /* checks for common ingredients */
            if (strcmp(filteredRecipes.ingredients[i].name, ingredients[j].name) == 0 && ingredients[j].amount[0] >= filteredRecipes.ingredients[i].amount[0])
            {
                commonIngredients++;
            }
        }
        /* if the nested loop didn't find an ingredient in the recipe that corresponds to the ones entered by the user then add ingredient to array */
        if (commonIngredients < 1)
        {
            missingIngredients[index] = malloc(strlen(ingredients[i].name) + 1);
            strcpy(missingIngredients[index], filteredRecipes.ingredients[i].name);
            index++;
        }
    }
    return missingIngredients;
}