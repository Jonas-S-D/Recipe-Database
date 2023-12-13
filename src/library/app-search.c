// Binary search function
int binary_search_recipes(Name_index *name_index_arr, int high, const char *target) {
    int low = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        int comparison = strcmp(name_index_arr[mid].name, target);

        // Check if the target is present at the middle
        if (comparison == 0) {
            return name_index_arr[mid].index;
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
char* string_to_lower(const char* str) {
    // Calculate the length of the input string
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // Allocate memory for char array
    char* lower_str = (char*)malloc((length + 1) * sizeof(char));

    // Check if memory allocation is successful
    if (lower_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Convert each character to lowercase
    for (int i = 0; i < length; i++) {
        lower_str[i] = tolower(str[i]);
    }

    // Add the null terminator
    lower_str[length] = '\0';
    return lower_str;
}

//function to create an array of structs containing recipe names and their index
Name_index *name_index_arr(Recipe *recipes, int recipe_count) {
    Name_index *name_index_struct_array;

    //allocate memory for the array
    name_index_struct_array = (Name_index *) malloc(sizeof(Name_index) * recipe_count);

    // add recipe names and indexes to array
    for (int i = 0; i < recipe_count; i++) {
        strcpy(name_index_struct_array[i].name, string_to_lower(recipes[i].name));
        name_index_struct_array[i].index = i;
    }

    return name_index_struct_array;
}
