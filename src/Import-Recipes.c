// Created by Kristoffer Holm on 16/11/2023.

#include <stdio.h>
#include <string.h>

int main() {
    FILE *recipes = fopen("src/Recipes.csv", "r");

    if (!recipes)
        printf("Can't open file\n");

    else {
        char buffer[2048];

        int row = 0;
        int column = 0;

        while (fgets(buffer, 1024, recipes)) {
            column = 0;
            row++;

            if (row == 0)
                continue;

            // Splitting the data
            char *string = strtok(buffer, ", ");

            while (string) {

                // Column 1
                if (column == 0) {
                    printf("Recipe : ");
                }

                // Column 2
                if (column == 1) {
                    printf("\tIngredients : ");
                }

                printf("%s ", string);
                string = strtok(NULL, ", ");
                ++column;
            }

            printf("\n");
        }

        fclose(recipes);
    }
    return 0;
}
