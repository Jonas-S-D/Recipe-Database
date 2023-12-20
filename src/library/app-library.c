#include "app-library.h"

/**
 * Gets user input for what they would like to do.
 * The user can chose to enter "i" for ingredients or "k" for categories or "s" for search,
 * "f" for done and "q" to shut down the program
 * @param ingredients Is the struct "Ingredient" that has been defined in "app-library.h"
 * @param ingredientCount Counts how many ingredients have been entered.
 * @param categories The category of food that the user wants.
 * @param categoryCount Counts how many categories have been entered.
 * @param recipes Array of recipes.
 * @param recipeCount Number of recipes in the array.
 * @param uniqueCategories Array containing unique categories.
 * @param uniqueCategoriesCount Number of unique categories.
 */
void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount, Recipe *recipes,
               int recipeCount, char uniqueCategories[MAX_CAT][MAX_NAME], int uniqueCategoriesCount) {
    char option[3]; // Allocate memory for option
    printf("Hvad vil du gerne goere?\n");

    while (1) {
        printf("Indtast 'i' for ingredienser, 'k' for kategorier, 's' for at soege efter specifikke opskrifter, 'f' naar du er faerdig og 'q' hvis du helt vil afslutte programmet>");
        scanf("%s", option);

        if (strcmp(option, "q") == 0) {
            exit(0);
        } else if (strcmp(option, "i") == 0) {
            userInputIngredients(ingredients, ingredientCount);
        } else if (strcmp(option, "k") == 0) {
            userInputCategories(categories, categoryCount, uniqueCategories, uniqueCategoriesCount);
        } else if (strcmp(option, "s") == 0) {
            userInputSearch(recipes, recipeCount);
        } else if (strcmp(option, "f") == 0) {
            if (*ingredientCount == 0) {
                printf("Du skal minimum indtaste 1 ingrediens for at fortsaette\n");
                continue;
            }
            break;
        } else {
            printf("Ugyldigt input!\n");
        }
    }
}

/**
 * Gets user input for ingredients
 * here the user can enter as many ingredients as they want and type 'f' when they are finished
 * @param ingredients Pointer to the struct "Ingredient" that has been defined in "app-library.h".
 * @param ingredientCount Pointer to the variable counting the number of ingredients entered.
 */
void userInputIngredients(Ingredient **ingredients, int *ingredientCount) {
    printf("Indtast de ingredienser du har, indtast 'f' naar du er faerdig:\n");

    Ingredient ingredient;
    *ingredients = NULL;

    while (1) {
        printf("Ingrediens %d >", *ingredientCount + 1);

        clearInputBuffer();
        fscanf(stdin, "%99[^\n]", ingredient.name);

        // Convert user input to lowercase.
        convertTolower(ingredient.name);

        if (strcmp(ingredient.name, "f") == 0) {
            return;
        }

        // Loop to handle user input being valid.
        do {
            printf("Ingrediens %d > Maengde & maaleenhed:", *ingredientCount + 1);
            // Checks if the user inputs 2 inputs that are valid a double and a char.

            if (scanf("%lf %s", ingredient.amount, ingredient.unit) != 2) {
                printf("Ugyldigt input. Indtast venligst baade maengde og enhed.\n");
                clearInputBuffer();
                continue; // Ask the user to enter the values again
            }

            // Convert user input to lowercase for comparison
            convertTolower(ingredient.unit);

            // Check if the user input is within the acceptable units string
            if (strstr(ACCEPTABLE_UNITS, ingredient.unit) != NULL) {
                break; // Exit the loop when a valid unit is entered
            } else {
                printf("%s: Ugyldig enhed. Gyldige enheder er: g, kg, stk, dl, ml, l\n", ingredient.unit);
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
 * Gets user input for categories.
 * The user can enter categories as they want and type 'f' when they are finished.
 * @param categories Pointer to the category of food that the user wants.
 * @param categoryCount Pointer to the variable counting the number of categories entered.
 * @param uniqueCategories Array containing unique categories.
 * @param uniqueCategoriesCount Number of unique categories.
 */
void userInputCategories(char ***categories, int *categoryCount, char uniqueCategories[MAX_CAT][MAX_NAME],
                         int uniqueCategoriesCount) {
    char category[MAX_NAME];
    printf("Indtast kategorier, du er interesseret i, indtast 'i' for information om tilgaengelige kategorier, indtast 'f', naar du er faerdig\n");

    while (1) {
        printf(">");
        // Use fgets to read the entire line, including spaces
        if (fgets(category, sizeof(category), stdin) == NULL) {
            printf("Fejl ved indlaesning. Afslutter...\n");
            exit(EXIT_FAILURE);
        }
        category[strcspn(category, "\n")] = '\0';

        // Convert user category input to lowercase.
        convertTolower(category);

        if (strcmp(category, "f") == 0) {
            return;  // Return to the menu
        } else if (strcmp(category, "i") == 0) {
            printCategories(uniqueCategories, uniqueCategoriesCount);
        } else {

            int validCategory = 0;

            for (int i = 0; i < MAX_CAT; i++) {
                if (strcmp(uniqueCategories[i], category) == 0) {
                    validCategory = 1;
                    break; // Exit the loop when a valid category is entered
                }
            }

            // Process the entered category
            if (validCategory) {
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
            } else {
                printf("Ugyldig kategori. Proev igen\n");
            }
        }
    }
}

/**
 * Prints all the different categories in the array of recipes.
 * @param uniqueCategories Array of all category names in the array of recipes.
 * @param uniqueCategoriesCount The number of categories in the uniqueCategories array.
 */
void printCategories(char uniqueCategories[MAX_CAT][MAX_NAME], int uniqueCategoriesCount) {
    for (int i = 0; i < uniqueCategoriesCount; i++) {
        printf("%s, ", uniqueCategories[i]);
    }
    printf("\n");
}

/**
 * Releases memory blocks from the allocated "realloc function" in "userInputIngredients" and "userInputCategories"
 * @param array is the location to free
 * @param count is the size which is being freed from the array
 */
void freeMemory(char ***array, int count) {
    for (int i = 0; i < count; ++i) {
        free((*array)[i]);
    }
    free(*array);
    *array = NULL;
}

//prints the initial program explanation
void printProgramExplanation() {
    printf("\nProgramforklaring:\n"
           "I dette program kan du indtaste alle dine ingredienser,\n"
           "og vil ud fra dem blive forslaaet opskrifter du er taet paa at kunne lave.\n"
           "Du vil ogsaa have mulighed for at indtaste en raekke kategorier, dette vil indsnaevre dit udvalg af opskrifter.\n"
           "Hvis du leder efter en specifik ret, kan du soege efter alle retter fra programmet.\n"
           "Naar alt det oenskede er indtastet, kan du fortsaette for at vaelge mellem tre retter.\n"
           "Efter dit valg af ret, vil hele opskriften blive udskrevet.\n"
           "Til den valgte opskrift vil blive en liste af dine manglede ingredienser, samt hvor de kan koebes billigst.\n\n");
}

/**
 * Allows the user to choose which of the three best recipes they want to see,
 * and then prints it out via a switch statement.
 * @param chosenRecipe The array of Recipe structs from which the user can choose.
 * @return The user's choice (1, 2, or 3).
 */
int chooseRecipe(const Recipe *chosenRecipe) {
    int userChoice = 0;
    /*
     * Koden udskriver de tre opskrifter med færrest manglende ingredienser,
     * ved samme på antal manglende ingredienser, vælger den de første i sorteringen.
     */
    for (int i = 0; i < 3; ++i) {
        printf("\nOpskrift %d %s (Manglende ingredienser: %d)", i + 1, chosenRecipe[i].name,
               chosenRecipe[i].missingIngredients);
    }
    printf("\n\n");
    /*
     * Lader brugeren vælge hvilken af de 3 udprintede opskrifter som de vil se detaljerne på.
    */
    while (1) {
        printf("Tast 1,2 eller 3 for at vaelge en opskrift\n");
        //tjekker om brugerens input ikke er et tal i forhold til det skal være en int.
        if (scanf("%d", &userChoice) != 1) {
            printf("\nForkert input.  Indtast venligst et tal.\n");
            clearInputBuffer();
            continue;
        }
        // Switch case der fungere til 1, 2, og 3, hvis ikke forkert input og prøv igen.
        switch (userChoice) {
            case (1):
            case (2):
            case (3):
                printRecipe(chosenRecipe[userChoice - 1]);
                return userChoice;
            default:
                printf("\nForkert input. Indtast venligst 1, 2, eller 3.\n");
        }
    }
}

/**
 * Allows the user to search for a recipe in the array of recipes.
 * @param recipes The array of Recipe structs containing all recipes.
 * @param recipeCount The number of recipes in the array of recipes.
 */
void userInputSearch(Recipe *recipes, int recipeCount) {
    // initialize loop variable
    int outerLoop = 1;

    // run loop until user want to break it
    while (outerLoop == 1) {

        //initialize char arrays and inner loop variable
        char target[MAX_NAME];
        char breakLoop[1];
        int innerLoop = 1;
        int targetRecipeSearch = -1;

        //ask user for recipe or whether to finish search
        printf("indtast opskrift du oensker at finde, indtast 'l' hvis du vil se en liste af opskrifter i"
               " biblioteket, og 'f' for at afslutte og gaa tilbage til hovedmenuen\n>");
        scanf(" %[^\n]", target);
        //perform user choice
        if (strcmp(target, "f") == 0) {
            break;
        } else if (strcmp(target, "l") == 0) {
            printRecipeNames(recipes, recipeCount);
        } else {
            targetRecipeSearch = searchRecipe(recipes, recipeCount, target);
            //if recipe found, print recipe
            if (targetRecipeSearch != -1) {
                printRecipe(recipes[targetRecipeSearch]);
            }
                //otherwise tell user not the recipe is not in library
            else {
                printf("desvaerre, der er ikke en opskrift med det navn i opskrift biblioteket.\n");

                //inner loop to co ask the user if they want to try again or exit
                while (innerLoop == 1) {
                    printf("Tast 'j' for at proeve igen og 'f' for at gaa tilbage til hovedmenuen.\n>");
                    scanf(" %s", breakLoop);
                    strcpy(breakLoop, stringToLower(breakLoop));

                    //if statement to break innerLoop or continue if unacceptable input is input
                    if (strcmp(stringToLower(breakLoop), "j") == 0) {
                        outerLoop = 1;
                        innerLoop = 0;
                    } else if (strcmp(stringToLower(breakLoop), "f") == 0) {
                        outerLoop = 0;
                        innerLoop = 0;
                    } else {
                        printf("Ugyldigt input!\n");
                    }
                }
            }
        }
    }
}

/**
 * Converts each character in a string to lowercase.
 * @param str The string to be converted to lowercase.
 */
void convertTolower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char) tolower(str[i]);
    }
}

/**
 * Clears the buffer for standard input stream.
 */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Prints the names of recipes.
 * @param recipes The array of recipes to extract names from.
 * @param recipeCount The number of recipes in the array.
 */
void printRecipeNames(Recipe *recipes, int recipeCount) {
    printf("*******************************************************************\n");
    for (int i = 0; i < recipeCount; i++) {
        printf("Opskrift %d: %s\n", i + 1, recipes[i].name);
    }
    printf("*******************************************************************\n");
}

/**
 * Searches for a recipe in the array of recipes.
 * @param recipes The array of recipes to search in.
 * @param recipeCount The number of recipes in the array.
 * @param target The name of the recipe to search for.
 * @return The index of the found recipe, or -1 if not found.
 */
int searchRecipe(Recipe *recipes, int recipeCount, char *target) {
    //convert input char array to lower case
    strcpy(target, stringToLower(target));

    //create a name index array with library recipes
    nameIndex *recipeNameIndex = nameIndexArr(recipes, recipeCount);

    //test whether the user recipe is in the recipe library
    int targetRecipe = binarySearchRecipes(&recipeNameIndex[0], recipeCount, target); //search for recipe
    freeNameIndexArr(recipeNameIndex);
    return targetRecipe;
}