#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// Function to create a new file in the current directory
void create_file() {
    char filename[256];
    FILE *file;
    
    printf("Enter the file name to create: ");
    scanf("%s", filename);
    
    // Create the file (this will create a zero-length file)
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
    } else {
        printf("File %s created successfully.\n", filename);
        fclose(file);
    }
}

// Function to list all files in the current directory
void list_files() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        printf("Error: Could not open current directory.\n");
        return;
    }

    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." (current and parent directories)
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

// Function to delete a file from the current directory
void delete_file() {
    char filename[256];

    printf("Enter the file name to delete: ");
    scanf("%s", filename);

    if (remove(filename) == 0) {
        printf("File %s deleted successfully.\n", filename);
    } else {
        printf("Error: Could not delete file %s\n", filename);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nFile Organization Menu:\n");
        printf("1. Create a file\n");
        printf("2. List all files\n");
        printf("3. Delete a file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_file();
                break;
            case 2:
                list_files();
                break;
            case 3:
                delete_file();
                break;
            case 4:
                printf("Exiting the program...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

