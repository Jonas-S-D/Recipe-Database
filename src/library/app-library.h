#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CAT 100
#define MAX_NAME 100
#define MAX_EXPLANATION 2000
#define MAX_AMOUNT 20
#define MAX_LINE 1000
#define MAX_UNIT 5
#define ACCEPTABLE_UNITS "g stk dl ml l kg"

// Define the struct for ingredients
typedef struct {
    char name[MAX_NAME]; //char array for name of ingredient
    double amount[MAX_AMOUNT]; //double array for amount of ingredient needed
    char unit[MAX_UNIT]; //char array for units (g, ml, stk)
} Ingredient;

// Define the struct for recipes
typedef struct {
    char name[MAX_NAME]; //char array for name
    char categories[MAX_CAT][MAX_NAME]; //pointer to char arrays for categories
    char explanation[MAX_EXPLANATION]; //char array for recipe explanation
    int missingIngredients;
    Ingredient *ingredients; // Dynamic array for ingredients
} Recipe;

void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount);
void userInputIngredients(Ingredient **ingredients, int *ingredientCount);
void userInputCategories(char ***categories, int *categoryCount);
void freeMemory(char ***array, int count);
void printProgramExplanation();

// Load
int load_recipe_struct(FILE *file, Recipe **recipes);
void check_load(FILE *file);
void parse_categories(FILE *file, Recipe *recipe);
void parse_explanation(FILE *file, Recipe *recipe);
void print_recipe(Recipe recipe);
void parse_ingredients(FILE *file, Recipe *recipe);
void print_recipes(Recipe *recipes, int recipe_count);

// Compare
Recipe* filterRecipe(const Recipe* recipe, char** categories, int CategoryCount);
Recipe* filterRecipes(const Recipe* recipes, char** categories, int CategoryCount, int RecipeCount, int *filteredCount);
void sortFilteredRecipes(Recipe *FilteredRecipes, Ingredient *ingredients, int ingredientCount);
void sortRecipes(Recipe* FilteredRecipe, Ingredient* ingredients, int ingredientCount);
void qsortFunction(Recipe *FilteredRecipe, int size);
int compareFunction(const void *a, const void *b);
int unitCompare(Recipe* FilteredRecipe, Ingredient *ingredients, int recipe, int userInput);
void unitConvert(char *unit, double *amount);