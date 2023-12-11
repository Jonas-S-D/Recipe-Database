#include "app-library.h"

int load_recipe_struct(FILE *file, Recipe **recipes) {
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
            parse_categories(file, &(*recipes)[recipeCount]);

            // Parse recipe explanation
            parse_explanation(file, &(*recipes)[recipeCount]);

            // Parse ingredients
            parse_ingredients(file, &(*recipes)[recipeCount]);

            // Increment recipeCount
            recipeCount++;
        }
    }
    return recipeCount;
}

//function to check if file has been loaded
void check_load(FILE *file) {
    if (file == NULL) { //report if it ran into an error
        perror("Fejl ved aabning af fil");
        exit(EXIT_FAILURE);
    }
}

//function to print recipe
void print_recipe(Recipe recipe) {
    printf("**************************************************\n");
    printf("Opskriftens navn: %s\n\n", recipe.name);
    for (int i = 0; recipe.categories[i][0] != '\0'; i++) {
        printf("opskrifts kategorier: %s\n", recipe.categories[i]);
    }
    printf("\n");
    printf("Opskrifts beskrivelse: %s\n\n", recipe.explanation);
    for (int j = 0; recipe.ingredients[j].name[0] != '\0'; j++) {
        printf("Opskrifts ingrediens %d hedder: %s og du skal bruge %.1lf %s\n", j + 1, recipe.ingredients[j].name,
               *recipe.ingredients[j].amount, recipe.ingredients[j].unit);
    }
    printf("\n");
}

//function to print all recipes in struct array
void print_recipes(Recipe *recipes, int recipe_count) {
    printf("Antal opskrifter: %d\n", recipe_count);
    for (int i = 0; i < recipe_count; i++) {
        printf("Udskriver opskrift %d\n", i + 1);
        print_recipe(recipes[i]);
    }
}

//function to parse categories
void parse_categories(FILE *file, Recipe *recipe) {
    char line[MAX_LINE];
    fgets(line, sizeof(line), file);
    sscanf(line, ">%[^\n]", line);
    int count = 0;
    char *token = strtok(line, ",\n");

    while (token != NULL && count < MAX_CAT) {
        strcpy(recipe->categories[count], token);
        token = strtok(NULL, ",\n");
        count++;
        if (token == NULL) {
            recipe->categories[count][0] = '\0';
        }
    }
}

//function to parse explanation
void parse_explanation(FILE *file, Recipe *recipe) {
    char line[MAX_LINE];
    fgets(line, sizeof(line), file);
    sscanf(line, ">%[^\n]", recipe->explanation);
    while (*fgets(line, sizeof(line), file) != '>') {
        strcat(recipe->explanation, line);
    }
}

//function to parse ingredients in recipe
void parse_ingredients(FILE *file, Recipe *recipe) {
    char line[MAX_LINE];
    int ingredientCount = 0;

    // Initialize dynamic array for ingredients
    recipe->ingredients = NULL;

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

    // Null-terminate the ingredients array
    recipe->ingredients = realloc(recipe->ingredients, (ingredientCount + 1) * sizeof(Ingredient));
    recipe->ingredients[ingredientCount].name[0] = '\0';
    recipe->ingredients[ingredientCount].amount[0] = '\0';
}