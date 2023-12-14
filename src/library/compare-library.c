// Filter loaded recipes by category
Recipe *filterRecipe(const Recipe *recipe, char **categories, int CategoryCount) {
    Recipe *filteredRecipe = malloc(sizeof(Recipe)); // Dynamically allocates FilteredRecipe
    if (filteredRecipe == NULL) {
        printf("Memory allocation failed for FilteredRecipe.\n");
        return NULL;
    }
    filteredRecipe->name[0] = '\0';

    if (categories != NULL && CategoryCount > 0) { // At least one category chosen
        for (int i = 0; i < CategoryCount; ++i) { // Checks through the users categories
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
void findLowestPrice(char missingIngredients[][MAX_NAME], int arrLength) {
    /* opens file and returns an error if file pointer points to NULL */
    FILE *file = fopen("priser.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    Item *item;
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
    item = malloc(structLength * sizeof(Item));
    if (item == NULL) {
        printf("Failed to allocate memory\n");
        fclose(file);
        return;
    }

    /* scans data from file into array of structs */
    int count = 0;
    while (!feof(file)) {
        fscanf(file, "%[^,], %[^,], %lf,\n", item[count].store, item[count].name, &item[count].price);
        count++;
    }
    fclose(file);

    /* variables used to save each ingredient, the lowest price and the store which it can be bought */
    char storeName[MAX_NAME];
    char itemName[MAX_NAME];
    double lowestPrice = 1000;

    /* searches for which store has the lowest price for each ingredient */
    for (int i = 0; i < arrLength; i++) {
        lowestPrice = 1000;
        for (int j = 0; j < structLength; j++) {
            if (strcmp(missingIngredients[i], item[j].name) == 0 && lowestPrice > item[j].price) {
                lowestPrice = item[j].price;
                strcpy(storeName, item[j].store);
                strcpy(itemName, item[j].name);
            }
        }
        /* checks if ingredient was found in the struct array */
        if (strcmp(missingIngredients[i], itemName) == 0) {
            printf("Billigste %s kan kobes i %s for %.2lf kr.\n", itemName, storeName, lowestPrice);
        } else {
            printf("%s kan ikke findes i databasen\n", missingIngredients[i]);
        }
    }
    free(item);
}