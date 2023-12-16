/**
 * Binary search function
 * @param *nameIndexArr pointer to the array to be searched.
 * @param high variable containing last index of array.
* @param *target pointer to the string to search for.
 */
int binarySearchRecipes(nameIndex *nameIndexArr, int high, const char *target) {
    int low = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        int comparison = strcmp(nameIndexArr[mid].name, target);

        // Check if the target is present at the middle
        if (comparison == 0) {
            return nameIndexArr[mid].index;
        }

        // If the target is in the left half
        if (comparison > 0) {
            high = mid - 1;
        }
            // If the target is in the right half
        else {
            low = mid + 1;
        }
    }

    // If the target is not present in the array return -1
    return -1;
}

/**
 * function that converts a string to lower case
 * @param *str pointer to the string to be converted to lower case.
 */
char *stringToLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char) tolower(str[i]);
    }
    return str;
}

//
/**
 * function to create an array of structs containing recipe names and their index
 * @param *recipes pointer to the array of recipe to generate a nameIndex array based on.
 */
nameIndex *nameIndexArr(Recipe *recipes, int recipeCount) {
    nameIndex *nameIndexStructArray;

    //allocate memory for the array
    nameIndexStructArray = (nameIndex *) malloc(sizeof(nameIndex) * recipeCount);

    // add recipe names and indexes to array
    for (int i = 0; i < recipeCount; i++) {
        strcpy(nameIndexStructArray[i].name, stringToLower(recipes[i].name));
        nameIndexStructArray[i].index = i;
    }

    return nameIndexStructArray;
}