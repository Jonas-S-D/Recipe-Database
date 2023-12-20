#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CAT 20
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

typedef struct
{
    char name[MAX_NAME];
    char store[MAX_NAME];
    char unit[MAX_UNIT];
    double price;
} Item;

typedef struct {
    char name[MAX_NAME]; //char array for name
    int index; //array to hold index of recipe
} nameIndex;

void convertTolower(char* str);
void userInput(Ingredient **ingredients, int *ingredientCount, char ***categories, int *categoryCount, Recipe *recipes, int recipeCount, char uniqueCategories[MAX_CAT][MAX_NAME], int uniqueCategoriesCount);
void userInputIngredients(Ingredient **ingredients, int *ingredientCount);
void userInputCategories(char ***categories, int *categoryCount, char uniqueCategories[MAX_CAT][MAX_NAME], int uniqueCategoriesCount);
void printCategories(char uniqueCategories[MAX_CAT][MAX_NAME], int uniqueCategoriesCount);
void freeMemory(char ***array, int count);
void printProgramExplanation();
int chooseRecipe(const Recipe* chosenRecipe);
void printRecipeNames(Recipe *recipes, int recipeCount);

// Load
int loadRecipeStruct(FILE *file, Recipe **recipes, char uniqueCategories[MAX_CAT][MAX_NAME], int *uniqueCategoriesCount);
void checkLoad(FILE *file);
void parseCategories(FILE *file, Recipe *recipe, char uniqueCategories[MAX_CAT][MAX_NAME], int *uniqueCategoriesCount);
void parseExplanation(FILE *file, Recipe *recipe);
void printRecipe(Recipe recipe);
void parseIngredients(FILE *file, Recipe *recipe);

// Compare
Recipe* filterRecipe(const Recipe* recipe, char** categories, int categoryCount);
void filterRecipeCategories(const Recipe *recipe, char **categories, Recipe *filteredRecipe, int i);
Recipe* filterRecipes(const Recipe* recipes, char** categories, int categoryCount, int recipeCount, int *filteredCount);
void missingIngredientsAllRecipes(Recipe *filteredRecipes, Ingredient *ingredients, int ingredientCount);
void countMissingIngredients(Recipe* filteredRecipe, Ingredient* ingredients, int ingredientCount);
int qsortCompare(const void *a, const void *b);
void userInputSearch(Recipe *recipes, int recipeCount);
int unitCompare(Recipe* filteredRecipe, Ingredient *ingredients, int recipe, int userInput);
void unitConvert(char *unit, double *amount);
void clearInputBuffer();
int recipeHasCategory(const Recipe *recipe, const char *category);

//search
int binarySearchRecipes(nameIndex *nameIndexArr, int high, char *target);
char* stringToLower(char *str);
nameIndex *nameIndexArr(Recipe *recipes, int recipeCount);
int searchRecipe(Recipe *recipes, int recipeCount, char *target);
void freeNameIndexArr(nameIndex *nameIndexStructArray);


// Price Compare
void findLowestPrice(char **missingIngredients, int arrLength);
char **ingredientsNeeded(Recipe userChosenRecipe, int ingredientCount, Ingredient *ingredients);
