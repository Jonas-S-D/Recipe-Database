#include "../src/library/app-library.c"
#include "../src/library/load-library.c"
#include "../src/library/app-search.c"
#include <assert.h>

// Prototyper til test-funktioner
void loadRecipeTest(void);

int main(void) {
    //Kør alle test-funktioner.
    loadRecipeTest();
    printf("Great succes!!!");
}

// Unit_tests
void loadRecipeTest(void) {
    //load recipes into recipe array and initialize variables
    FILE *file = fopen("src/library/recipes.txt", "r");
    checkLoad(file);
    Recipe *recipes = NULL;
    char uniqueCategories[MAX_CAT][MAX_NAME];
    int uniqueCategoriesCount = 0;
    int recipeCount = loadRecipeStruct(file, &recipes,uniqueCategories,&uniqueCategoriesCount);

    //check loadRecipeStruct return
    assert(recipeCount == 4);

    //check loadRecipeStruct loading of name
    assert(strcmp(recipes[0].name, "Biksemad") == 0 && strcmp(recipes[3].name, "Oksekoeds lasagne") == 0);

    //check loadRecipeStruct loading of categories
    assert(strcmp(recipes[0].categories[0], "rester") == 0 && strcmp(recipes[3].categories[2], "koed") == 0);

    //check loadRecipeStruct loading of explanation
    assert(recipes[0].explanation[0] == 's' && recipes[3].explanation[0] == 'S');

    //check loadRecipeStruct loading of ingredient name amount and unit
    assert(strcmp(recipes[0].ingredients[0].name, "kartofler") == 0 &&
                   strcmp(recipes[3].ingredients[9].name, "pepper") == 0);
    assert(recipes[0].ingredients->amount[0] == 500 && recipes[3].ingredients->amount[0] == 500);
    assert(strcmp(recipes[0].ingredients[0].unit, "g") == 0 && strcmp(recipes[3].ingredients[1].unit, "stk") == 0);
}

int binarySearchRecipes(nameIndex *nameIndexArr, int high, const char *target) {

void *nameIndexArr(void) {

}

void binarySearchRecipes(void) {

}