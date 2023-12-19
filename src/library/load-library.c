/**
 * loads recipes from a txt file into an array of recipe structs.
 * The function returns the number of recipes loaded and directly loads recipes into **recipes
 * @param file the file that recipes are to be loaded from.
 * @param recipes The pointer to the array of recipe structs.
 * @param uniqueCategories The array where unique categories are loaded into.
 * @param uniqueCategoriesCount The variable holding the number of unique categories.
 * @return The amount of recipes loaded from the file.
 */
int loadRecipeStruct(FILE *file, Recipe **recipes, char uniqueCategories[MAX_CAT][MAX_NAME], int *uniqueCategoriesCount) {
    char line[MAX_LINE]; // char array to hold lines
    int recipeCount = 0;  // Variable to keep track of the number of recipes
    // Reading the file line by line
    while (fgets(line, sizeof(line), file) != NULL) { //run loop
        if (line[0] != '\n') {
            // Increase the size of the recipes array to accommodate new recipes
            *recipes = realloc(*recipes, (recipeCount + 1) * sizeof(Recipe));
            if (*recipes == NULL) { //report if it ran into an error
                perror("Fejl ved udvidelse af opskriftsarray");
                exit(EXIT_FAILURE);
            }

            // Parse recipe name
            sscanf(line, ">%[^\n]", (*recipes)[recipeCount].name);

            // Parse categories
            parseCategories(file, &(*recipes)[recipeCount], uniqueCategories, uniqueCategoriesCount);

            // Parse recipe explanation
            parseExplanation(file, &(*recipes)[recipeCount]);

            // Parse ingredients
            parseIngredients(file, &(*recipes)[recipeCount]);

            // Increment recipeCount
            recipeCount++;
        }
    }
    return recipeCount;
}

/**
 * function to check if file has been loaded
 * @param file the file that recipes are to be loaded from.
 */
void checkLoad(FILE *file) {
    if (file == NULL) { //report if it ran into an error
        perror("Fejl ved aabning af fil");
        exit(EXIT_FAILURE);
    }
}

/**
 * function to print a recipe
 * @param recipe is the recipe to be printed
 */
void printRecipe(Recipe recipe) {
    printf("**************************************************\n");
    printf("Opskriftens navn: %s\n\n", recipe.name);
    printf("Opskriftens kategorier: ");
    for (int i = 0; recipe.categories[i][0] != '\0'; i++) {
        printf("%s, ", recipe.categories[i]);
    }
    printf("\n\n");
    printf("Opskrifts beskrivelse: %s\n\n", recipe.explanation);
    for (int j = 0; recipe.ingredients[j].name[0] != '\0'; j++) {
        printf("Ingredients %d: %s, og du skal bruge %.1lf %s\n", j + 1, recipe.ingredients[j].name,
               *recipe.ingredients[j].amount, recipe.ingredients[j].unit);
    }
    printf("\n");
}

/**
 * Parses categories from a file and adds them to a recipe.
 * @param file the file that recpies are to be loaded from.
 * @param recipe the recipe to add categories to
 * @param uniqueCategories are the array the unique categories are loaded into
 * @param UniqueCategoriesCount the variable holding the number of unique categories.
 */
void parseCategories(FILE *file, Recipe *recipe, char uniqueCategories[MAX_CAT][MAX_NAME], int *uniqueCategoriesCount) {
    char line[MAX_LINE];
    fgets(line, sizeof(line), file);
    sscanf(line, ">%[^\n]", line);
    int count = 0;
    char *token = strtok(line, ",\n");

    while (token != NULL) {
        // add token to recipe categories
        strcpy(recipe->categories[count], token);

        // Check if the category is already in unique categories array
        int unique = 1;

        for (int i = 0; i < *uniqueCategoriesCount; i++) {
            if (strcmp(uniqueCategories[i], token) == 0) {
                unique = 0;
                break;
            }
        }

        if (unique == 1) {
            strcpy(uniqueCategories[*uniqueCategoriesCount], token);
            *uniqueCategoriesCount = *uniqueCategoriesCount + 1;
        }
        token = strtok(NULL, ",\n");
        count++;
    }
}

/**
 * Parses explanation from a file and adds it to a recipe.
 * @param file the file that recpies are to be loaded from.
 * @param recipe The recipe to add an explanation to.
 */
void parseExplanation(FILE *file, Recipe *recipe) {
    char line[MAX_LINE];
    fgets(line, sizeof(line), file);
    sscanf(line, ">%[^\n]", recipe->explanation);
    while (*fgets(line, sizeof(line), file) != '>') {
        strcat(recipe->explanation, line);
    }
}

/**
 * function to parse ingredients in recipe
 * @param file the file that recpies are to be loaded from.
 * @param recipe the recipe to add categories to
 */

void parseIngredients(FILE *file, Recipe *recipe) {
    char line[MAX_LINE];
    int ingredientCount = 0;

    // Initialize dynamic array for ingredients
    recipe->ingredients = NULL;
    recipe->missingIngredients = 0;

    do {
        recipe->ingredients = realloc(
                recipe->ingredients, (ingredientCount + 1) * sizeof(Ingredient));

        // Check if the line starts with '>'
        if (line[0] == '>') {
            // Skip the first character
            sscanf(line + 1, "%30[^,], %lf %3s", recipe->ingredients[ingredientCount].name,
                   recipe->ingredients[ingredientCount].amount,
                   recipe->ingredients[ingredientCount].unit);
        } else {
            // If the line doesn't start with '>', use the original sscanf
            sscanf(line, "%30[^,], %lf %3s", recipe->ingredients[ingredientCount].name,
                   recipe->ingredients[ingredientCount].amount,
                   recipe->ingredients[ingredientCount].unit);
        }

        ingredientCount++;
    } while (fgets(line, sizeof(line), file) != NULL && line[0] != '>' && line[0] != '\n');
    recipe->ingredients[ingredientCount].name[0] = '\0';
}