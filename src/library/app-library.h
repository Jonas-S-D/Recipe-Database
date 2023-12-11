#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CAT 100
#define MAX_NAME 100
#define MAX_EXPLANATION 2000
#define MAX_AMOUNT 20
#define MAX_LINE 1000
#define Max_UNIT 5
#define ACCEPTABLE_UNITS "g stk dl ml l"

// Define the struct for ingredients
typedef struct {
    char name[MAX_NAME]; //char array for name of ingredient
    double amount[MAX_AMOUNT]; //char array for amount of ingredient needed
    char unit[Max_UNIT]; //char array for units (g, ml, stk)
} Ingredient;

// Define the struct for recipes
typedef struct {
    char name[MAX_NAME]; //char array for name
    char categories[MAX_CAT][MAX_NAME]; //pointer to char arrays for categories
    char explanation[MAX_EXPLANATION]; //char array for recipe explanation
    Ingredient *ingredients; // Dynamic array for ingredients
} Recipe;

void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount);
void userInputIngredients(Ingredient **ingredients, int *ingredientCount);
void userInputCategories(char ***categories, int *categoryCount);
void freeMemory(char ***array, int count);
void printProgramExplanation();
int load_recipe_struct(FILE *file, Recipe **recipes);
void check_load(FILE *file);
void parse_categories(FILE *file, Recipe *recipe);
void parse_explanation(FILE *file, Recipe *recipe);
void print_recipe(Recipe recipe);
void parse_ingredients(FILE *file, Recipe *recipe);
void print_recipes(Recipe *recipes, int recipe_count);
