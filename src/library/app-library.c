#include "app-library.h"

/**
 * Gets user input for what they would like to do.
 * The user can chose to enter "i" for ingredients or "c" for categories or "d" for done
 * @param ingredients Is the struct "Ingredient" that has been defined in "app-library.h"
 * @param ingredientCount Counts how many ingredients have been entered
 * @param categories The category of food that the user wants
 * @param categoryCount Counts how many categories have been entered
 */
void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount, Recipe *recipes,
               int recipeCount) {
    char option[3]; // Allocate memory for option
    printf("Hvad vil du gerne goere?\n");

    while (1) {
        printf("Indtast 'i' for ingredienser, 'k' for kategorier, 's' for at soege efter specifikke opskrifter, og 'f' naar du er faerdig>");
        scanf("%s", option);

        if (strcmp(option, "i") == 0) {
            userInputIngredients(ingredients, ingredientCount);
        } else if (strcmp(option, "k") == 0) {
            userInputCategories(categories, categoryCount);
        } else if (strcmp(option, "s") == 0) {
            userInputSearch(recipes, recipeCount);
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
        for (int i = 0; ingredient.name[i]; i++) {
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
            for (int i = 0; ingredient.unit[i]; i++) {
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
        for (int i = 0; category[i]; i++) {
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

void userInputSearch(Recipe *recipes, int recipeCount) {
    // initialize loop variable
    int outer_loop = 1;

    // run loop until user want to break it
    while (outer_loop == 1) {

        //initialize char arrays and innner loop variable
        char target[MAX_NAME];
        char break_loop[MAX_NAME];
        int inner_loop = 1;

        //ask user for recipe or whether to finish search
        printf("indtast opskrift du oensker at finde og 'f' for at afslutte og gaa tilbage til hovedskaermen\n>");
        scanf(" %[^\n]", target);
        if (strcmp(target, "f") == 0) {
            break;
        }

        //convert input char array to lower case
        strcpy(target, string_to_lower(target));

        //create a name index array with library recipes
        Name_index *recipe_name_index = name_index_arr(recipes, recipeCount);

        //test whether the user recipe is in the recipe library
        int target_recipe = binary_search_recipes(&recipe_name_index[0], recipeCount, target); //search for recipe

        //if recipe found, print recipe
        if (target_recipe != -1) {
            print_recipe(recipes[target_recipe]);
        }
        //otherwise tell user not the recipe is not in library
        else {
            printf("desvaerre, der er ikke en opskrift med det navn i opskrift biblioteket.\n");

            //inner loop to co ask the user if they want to try again or exit
            while (inner_loop == 1) {
                printf("Tast ja for at proeve igen og nej for at gaa tilbage til hovedskaermen.\n>");
                scanf(" %s", break_loop);
                strcpy(break_loop, string_to_lower(break_loop));

                //if statement to break inner_loop or continue if unacceptable input is input
                if (strcmp(string_to_lower(break_loop), "ja") == 0) {
                    outer_loop = 1;
                    inner_loop = 0;
                } else if (strcmp(string_to_lower(break_loop), "nej") == 0) {
                    outer_loop = 0;
                    inner_loop = 0;
                }
                else{
                    printf("Ugyldigt input!\n");
                }

            }
        }
    }
}