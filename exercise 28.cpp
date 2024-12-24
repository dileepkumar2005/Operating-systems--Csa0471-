#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// Function to check if the pattern exists in the line
int contains_pattern(const char *line, const char *pattern) {
    return strstr(line, pattern) != NULL;
}

// Main function to simulate the GREP command
int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE_LENGTH];

    // Check if enough arguments are passed (at least pattern and filename)
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read each line from the file and search for the pattern
    while (fgets(line, sizeof(line), file)) {
        if (contains_pattern(line, argv[1])) {
            printf("%s", line); // Print the line if the pattern is found
        }
    }

    // Close the file
    fclose(file);
    return 0;
}

