#include "../src/library/app-library.c"
#include "../src/library/load-library.c"
#include <assert.h>

// Prototyper til test-funktioner
void load_recipe_test(void);

int main(void) {
    //Kør alle test-funktioner.
    load_recipe_test();
    printf("Great succes!!!");
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
    assert(strcmp(recipes[0].name, "Oksekoeds lasagne") == 0 && strcmp(recipes[3].name, "Biksemad") == 0);
    assert(strcmp(recipes[0].name, "Oksekoeds lasagne") == 0 && strcmp(recipes[3].name, "Biksemad") == 0);


    //check load_recipe_struct loading of categories
    assert(strcmp(recipes[0].categories[0], "varm aftensmad") == 0 && strcmp(recipes[3].categories[2], "varm aftensmad") == 0);

    //check load_recipe_struct loading of explanation
    assert(recipes[0].explanation[0] == 'S' && recipes[3].explanation[0] == 's');

    //check load_recipe_struct loading of ingredient name amount and unit
    assert(strcmp(&recipes[0].ingredients->name[0], "oksekoed") == 0 &&
                   strcmp(&recipes[3].ingredients->name[0], "kartofler") == 0);
    assert(recipes[0].ingredients->amount[0] == 500 && recipes[3].ingredients->amount[0] == 500);
    assert(strcmp(recipes[0].ingredients[0].unit, "g") == 0 && strcmp(recipes[3].ingredients[1].unit, "stk") == 0);
}
