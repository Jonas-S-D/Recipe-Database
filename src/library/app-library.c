#include "app-library.h"

void getUserInput(struct Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount) {
    char option[2]; // Allocate memory for option
    printf("What would you like to do?\n");

    while (1) {
        printf("Enter 'i' for ingredients or 'c' for categories: ");
        scanf("%s", option);
        printf("%s", option);

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
}

void getUserInputIngredients(struct Ingredient **ingredients, int *ingredientCount) {
    printf("Enter the ingredients you have (enter 'done' when finished)\n");

    struct Ingredient ingredient;
    *ingredients = NULL;

    while (1) {
        printf("Ingredient %d > ", *ingredientCount + 1);
        scanf("%s", ingredient.name);

        if (strcmp(ingredient.name, "done") == 0) {
            return;
        }

        printf("Ingredient %d > Amount: ", *ingredientCount + 1);
        scanf("%s", ingredient.amount);

        // Dynamically allocate memory for the new ingredient
        *ingredients = realloc(*ingredients, (*ingredientCount + 1) * sizeof(struct Ingredient));
        (*ingredients)[*ingredientCount] = ingredient;

        (*ingredientCount)++;
    }
}

void getUserInputCategories(char ***categories, int *categoryCount) {
    char category[MAX_NAME];
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

void printProgramExplanation() {
    printf("\nProgram explanation:\n"
           "The purpose of this program is so reduce the amount food waste in the users household.\n"
           "This is being done by comparing the users inventory of food and recommending the most relevant dishes.\n"
           "Dishes with the least amount of ingredients missing will be prioritized higher.\n"
           "The program works by requesting ingredients 'i' and a category 'c' of food.\n"
           "When the user has prompted the desired information a list of dishes will be printed.\n"
           "Now the user can choose a dish of their liking that will be printed together with the recipe.\n\n");
}
