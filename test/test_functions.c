#include "../src/library/app-library.h"
#include <assert.h>

/* Prototyper til test-funktioner */
void load_recipe_test(void);

int main(void) {
    /* Kør alle test-funktioner. */
    load_recipe_test();
}

// Unit_tests
void load_recipe_test(void) {
    //load recipes into recipe array and initialize variables
    FILE *file = fopen("src/library/recipes.txt", "r");
    check_load(file);
    Recipe *recipes = NULL;
    int recipeCount = load_recipe_struct(file, &recipes);

    //check load_recipe_struct return
    assert(recipeCount == 4);

    //check load_recipe_struct loading of name
    assert(recipes[0].name == "Oksekoeds lasagne" && recipes[3].name == "Biksemad");

    //check load_recipe_struct loading of categories
    assert(recipes[0].categories[0] == "varm aftensmad" && recipes[3].categories[2] == "varm aftensmad");

    //check load_recipe_struct loading of explanation
    assert(recipes[0].explanation[0] == 'S' && recipes[3].explanation[0] == 's');

    //check load_recipe_struct loading of ingredient name amount and unit
    assert(&recipes[0].ingredients->name[0] == "oksekoed" && &recipes[3].ingredients->name[0] == "kartofler");
    assert(recipes[0].ingredients->amount[0] == 500 && recipes[3].ingredients->amount[0] == 500);
    assert(&recipes[0].ingredients->unit[0] == "g" && &recipes[3].ingredients->unit[0] == "g");
}

