#include "app-library.h"

void getUserInput(char ***ingredients, int *ingredientCount, char ***categories, int *categoryCount) {
    char *option = (char *)malloc(2 * sizeof(char));  // Allocate memory for option
    printf("What would you like to do?\n");

    while (1) {
        printf("Enter 'i' for ingredients or 'c' for categories: ");
        scanf("%s", option);

        if (strcmp(option, "i") == 0) {
            getUserInputIngredients(ingredients, ingredientCount);
        } else if (strcmp(option, "c") == 0) {
            getUserInputCategories(categories, categoryCount);
        } else if (strcmp(option, "d") == 0) {
            break;
        } else {
            printf("Invalid input. Please enter 'i' or 'c': ");
        }
    }

    // Free allocated memory
    free(option);
}

void getUserInputIngredients(char ***ingredients, int *ingredientCount) {
    printf("Enter the ingredients you have (enter 'done' when finished)\n");

    char ingredient[MAX_INGREDIENT_LENGTH];
    *ingredients = NULL;

    while (1) {
        printf("Ingredient %d > ", *ingredientCount + 1);
        scanf("%s", ingredient);

        if (strcmp(ingredient, "done") == 0) {
            return;
        }

        // Dynamically allocate memory for the new ingredient
        *ingredients = realloc(*ingredients, (*ingredientCount + 1) * sizeof(char *));
        (*ingredients)[*ingredientCount] = strdup(ingredient);

        (*ingredientCount)++;
    }
}

void getUserInputCategories(char ***categories, int *categoryCount) {
    char category[MAX_NAME_LENGTH];
    printf("Enter categories you are interested in (enter 'done' when finished)\n");
    while (1) {
        printf(">");
        scanf("%s", category);

        if (strcmp(category, "done") == 0) {
            return;  // Return to the menu
        }

        // Dynamically allocate memory for the new category
        *categories = realloc(*categories, (*categoryCount + 1) * sizeof(char *));
        (*categories)[*categoryCount] = strdup(category);

        (*categoryCount)++;
    }
}

void freeMemory(char ***array, int count) {
    for (int i = 0; i < count; ++i) {
        free((*array)[i]);
    }
    free(*array);
    *array = NULL;
}