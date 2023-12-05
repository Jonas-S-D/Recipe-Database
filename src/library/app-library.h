#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CAT 100
#define MAX_NAME 100
#define MAX_EXPLANATION 2000
#define MAX_AMOUNT 20
#define MAX_LINE 1000

// Define the struct for ingredients
struct Ingredient {
    char name[MAX_NAME]; //char array for name of ingredient
    char amount[MAX_AMOUNT]; //char array for amount of ingredient needed
};

// Define the struct for recipes
struct Recipe {
    char name[MAX_NAME]; //char array for name
    char categories[MAX_CAT][MAX_NAME]; //pointer to char arrays for categories
    char explanation[MAX_EXPLANATION]; //char array for recipe explanation
    struct Ingredient *ingredients; // Dynamic array for ingredients
};

void getUserInput(struct Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount);
void getUserInputIngredients(struct Ingredient **ingredients, int *ingredientCount);
void getUserInputCategories(char ***categories, int *categoryCount);
void freeMemory(char ***array, int count);
void printProgramExplanation();