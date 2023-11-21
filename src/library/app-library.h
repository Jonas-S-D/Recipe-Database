#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_INGREDIENT_LENGTH 30

void getUserInput(char ***ingredients, int *ingredientCount, char ***categories, int *categoryCount);
void getUserInputIngredients(char ***ingredients, int *ingredientCount);
void getUserInputCategories(char ***categories, int *categoryCount);
void freeMemory(char ***array, int count);