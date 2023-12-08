#include "app-library.h"
/**
 * Gets user input for what they would like to do.
 * The user can chose to enter "i" for ingredients or "c" for categories or "d" for done
 * @param ingredients Is the struct "Ingredient" that has been defined in "app-library.h"
 * @param ingredientCount Counts how many ingredients have been entered
 * @param categories The category of food that the user wants
 * @param categoryCount Counts how many categories have been entered
 */
void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount) {
    char option[2]; // Allocate memory for option
    printf("What would you like to do?\n");

    while (1) {
        printf("Enter 'i' for ingredients, 'c' for categories, and 'd' when you are done>");
        scanf("%s", option);

        if (strcmp(option, "i") == 0) {
            userInputIngredients(ingredients, ingredientCount);
        } else if (strcmp(option, "c") == 0) {
            userInputCategories(categories, categoryCount);
        } else if (strcmp(option, "d") == 0) {
            break;
        } else {
            printf("Invalid input!\n");
        }
    }
}
/**
 * Gets user input for ingredients
 * here the user can enter as many ingredients as they want and type 'done' when they are finished
 * @param ingredients Is the struct "Ingredient" that has been defined in "app-library.h"
 * @param ingredientCount Counts the number of ingredients entered
 */
void userInputIngredients(Ingredient **ingredients, int *ingredientCount) {
    printf("Enter the ingredients you have, enter 'done' when finished:\n");

    Ingredient ingredient;
    *ingredients = NULL;

    while (1) {
        printf("Ingredient %d >", *ingredientCount + 1);
        scanf("%s", ingredient.name);

        if (strcmp(ingredient.name, "done") == 0) {
            return;
        }

        printf("Ingredient %d > Amount:", *ingredientCount + 1);
        scanf("%lf", ingredient.amount);

        // Dynamically allocate memory for the new ingredient
        *ingredients = realloc(*ingredients, (*ingredientCount + 1) * sizeof(Ingredient));
        (*ingredients)[*ingredientCount] = ingredient;

        (*ingredientCount)++;
    }
}
/**
 * Gets user input for categories
 * here the user can enter categories as they want and type 'done' when they are finished
 * @param categories The category of food that the user wants
 * @param categoryCount Counts the number of categories entered
 */
void userInputCategories(char ***categories, int *categoryCount) {
    char category[MAX_NAME];
    printf("Enter categories you are interested in, enter 'done' when finished\n");
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
/**
 * Releases memory blocks from the allocated "realloc function" in "userInputIngredients" and "userInputCategories"
 * @param array
 * @param count
 */
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
