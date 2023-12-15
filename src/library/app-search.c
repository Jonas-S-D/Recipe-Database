// Binary search function
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

    // If the target is not present in the array
    return -1;
}

//converts a string to lower case
char* stringToLower(const char* str) {
    // Calculate the length of the input string
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // Allocate memory for char array
    char* lowerStr = (char*)malloc((length + 1) * sizeof(char));

    // Check if memory allocation is successful
    if (lowerStr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Convert each character to lowercase
    for (int i = 0; i < length; i++) {
        lowerStr[i] = tolower(str[i]);
    }

    // Add the null terminator
    lowerStr[length] = '\0';
    return lowerStr;
}

//function to create an array of structs containing recipe names and their index
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
