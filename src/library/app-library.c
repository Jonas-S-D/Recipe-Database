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
    printf("Hvad vil du gerne goere?\n");

    while (1) {
        printf("Indtast 'i' for ingredienser, 'k' for kategorier og 'f', naar du er faerdig>");
        scanf("%s", option);

        if (strcmp(option, "i") == 0) {
            userInputIngredients(ingredients, ingredientCount);
        } else if (strcmp(option, "k") == 0) {
            userInputCategories(categories, categoryCount);
        } else if (strcmp(option, "f") == 0) {
            break;
        } else {
            printf("Ugyldigt input!\n");
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
    printf("Indtast de ingredienser du har, indtast 'faerdig' naar du er faerdig:\n");

    Ingredient ingredient;
    *ingredients = NULL;

    while (1) {
        printf("Ingrediens %d > ", *ingredientCount + 1);
        scanf("%s", ingredient.name);

        // Convert user input to lowercase.
        for (int i = 0; ingredient.name[i] != '\0'; i++) {
            ingredient.name[i] = (char) tolower(ingredient.name[i]);
        }

        if (strcmp(ingredient.name, "faerdig") == 0) {
            return;
        }

        // Loop to handle user input being valid.
        do {
            printf("Ingrediens %d > Maengde: ", *ingredientCount + 1);
            // Checks if the user inputs 2 inputs that are valid a double and a char.
            if (scanf("%lf %s", ingredient.amount, ingredient.unit) != 2) {
                while (getchar() != '\n');

                printf("Ugyldigt input. Indtast venligts baade beløb og enhed.\n");
                continue; // Ask the user to enter the values again
            }


            // Convert user input to lowercase for comparison
            for (int i = 0; ingredient.unit[i] != '\0'; i++) {
                ingredient.unit[i] = (char) tolower(ingredient.unit[i]);
            }

            // Check if the user input is within the acceptable units string
            if (strstr(ACCEPTABLE_UNITS, ingredient.unit) != NULL) {
                break; // Exit the loop when a valid unit is entered
            } else {
                printf("Ugyldig enhed. Proev igen\n");
            }

        } while (1); // Infinite loop until a valid unit is entered

        // Dynamically allocate memory for the new ingredient
        *ingredients = realloc(*ingredients, (*ingredientCount + 1) * sizeof(Ingredient));

        // Memory allocation failed
        if (*ingredients == NULL) {
            printf("Hukommelsestildeling mislykkedes. Afslutter.\n");
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
    printf("Indtast kategorier, du er interesseret i, indtast 'faerdig', naar du er faerdig\n");
    while (1) {
        printf(">");
        scanf("%s", category);

        // Convert user category input to lowercase.
        for (int i = 0; category[i] != '\0'; i++) {
            category[i] = (char) tolower(category[i]);
        }

        if (strcmp(category, "faerdig") == 0) {
            return;  // Return to the menu
        }

        // Dynamically allocate memory for the new category
        *categories = realloc(*categories, (*categoryCount + 1) * sizeof(char *));

        // Memory allocation failed
        if (*categories == NULL) {
            printf("Hukommelsestildeling mislykkedes. Afslutter.\n");
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
    printf("\nProgramforklaring:\n"
           "Formaalet med dette program er at reducere maengden af madspild i brugerens husstand.\n"
           "Dette goeres ved at sammenligne brugernes lager af foedevarer of anbefale de mest relevante madretter.\n"
           "Retter, hvor der mangler mindst maengder af ingredienser, vil blive prioriteret hoejere.\n"
           "Programmet fungerer ved at anmode om, ingredienserne 'i' og kategorierne 'k' af mad.\n"
           "Når brugerne har bedt om den oenskede information, udskrives en liste over madretter.\n"
           "Nu kan brugeren vaelge en madret som de gerne vil have udskrives sammen med opskriften.\n\n");
}
