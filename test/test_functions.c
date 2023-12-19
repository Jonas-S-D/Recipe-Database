#include "../src/library/app-library.c"
#include "../src/library/load-library.c"
#include "../src/library/search-library.c"
#include <assert.h>

// Prototypes for the test functions
void loadRecipeTest(void);
void SearchTest(void);

int main(void) {
    //run all test functions
    loadRecipeTest();
    SearchTest();
    printf("Great succes!!!");
}

// Unit tests
void loadRecipeTest(void) {
    //load recipes into recipe array and initialize variables
    FILE *file = fopen("src/library/recipes-test.txt", "r");
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

void SearchTest(void){
    //load recipes into recipe array and initialize variables
    FILE *file = fopen("src/library/recipes-test.txt", "r");
    checkLoad(file);
    Recipe *recipes = NULL;
    char uniqueCategories[MAX_CAT][MAX_NAME];
    int uniqueCategoriesCount = 0;
    int recipeCount = loadRecipeStruct(file, &recipes,uniqueCategories,&uniqueCategoriesCount);

    //check that searchRecipe can find a recipe even if it isnt writen in the same case as the array recipe
    char target[4][MAX_NAME] = {"BiKseMad","BolLer I KaRRy","Indbagte loeGRinge","Oksekoeds lasagne",};
    for (int i = 0; i < 3;i++){
        assert(searchRecipe(recipes,recipeCount,target[i]) == i);
    }

    //check that searchRecipe will not find a random string
    char target1[MAX_NAME];
    strcpy(target, "Jeg ELsker kage");
    assert(searchRecipe(recipes,recipeCount,target1) == -1);
}
