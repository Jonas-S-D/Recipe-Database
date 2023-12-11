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
        printf("Ingredient %d > ", *ingredientCount + 1);
        scanf("%s", ingredient.name);

        // Convert user input to lowercase.
        for (int i = 0; ingredient.name[i]; i++) {
            ingredient.name[i] = (char) tolower(ingredient.name[i]);
        }

        if (strcmp(ingredient.name, "done") == 0) {
            return;
        }

        // Loop to handle user input being valid.
        do {
            printf("Ingredient %d > Amount & Unit: ", *ingredientCount + 1);
            // Checks if the user inputs 2 inputs that are valid a double and a char.
            if (scanf("%lf %s", ingredient.amount, ingredient.unit) != 2) {
                while (getchar() != '\n');

                printf("Invalid input. Please enter both amount and unit.\n");
                continue; // Ask the user to enter the values again
            }


            // Convert user input to lowercase for comparison
            for (int i = 0; ingredient.unit[i]; i++) {
                ingredient.unit[i] = (char) tolower(ingredient.unit[i]);
            }

            // Check if the user input is within the acceptable units string
            if (strstr(ACCEPTABLE_UNITS, ingredient.unit) != NULL) {
                break; // Exit the loop when a valid unit is entered
            } else {
                printf("Invalid unit. Please try again.\n");
            }

        } while (1); // Infinite loop until a valid unit is entered

        // Dynamically allocate memory for the new ingredient
        *ingredients = realloc(*ingredients, (*ingredientCount + 1) * sizeof(Ingredient));

        // Memory allocation failed
        if (*ingredients == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            free(*ingredients);
            exit(EXIT_FAILURE);
        }

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

        // Convert user category input to lowercase.
        for (int i = 0; category[i]; i++) {
            category[i] = (char) tolower(category[i]);
        }

        if (strcmp(category, "done") == 0) {
            return;  // Return to the menu
        }

        // Dynamically allocate memory for the new category
        *categories = realloc(*categories, (*categoryCount + 1) * sizeof(char *));

        // Memory allocation failed
        if (*categories == NULL) {
            printf("Memory allocation failed. Exiting.\n");
            free(*categories);
            exit(EXIT_FAILURE);
        }

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
