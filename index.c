#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to copy a file
void copyFile(const char* source, const char* destination) {
    FILE* src = fopen(source, "rb");
    FILE* dest = fopen(destination, "wb");

    if (src == NULL || dest == NULL) {
        printf("Unable to open file\n");
        return;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied successfully from %s to %s\n", source, destination);
}

// Function to move a file
void moveFile(const char* source, const char* destination) {
    if (rename(source, destination) == 0) {
        printf("File moved successfully from %s to %s\n", source, destination);
    }
    else {
        printf("Unable to move file\n");
    }
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (remove(filename) == 0) {
        printf("File deleted successfully: %s\n", filename);
    }
    else {
        printf("Unable to delete file\n");
    }
}

// Function to search for a file (by name)
void searchFile(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file != NULL) {
        printf("File found: %s\n", filename);
        fclose(file);
    }
    else {
        printf("File not found: %s\n", filename);
    }
}

// Function to change file extension
void changeFileExtension(const char* source, const char* new_extension) {
    char destination[100];

    // Find the last dot '.' to replace the extension
    const char* dot_position = strrchr(source, '.');
    if (dot_position == NULL) {
        // No extension found, just add the new extension
        snprintf(destination, sizeof(destination), "%s.%s", source, new_extension);
    }
    else {
        // Copy source up to the dot and append the new extension
        size_t base_length = dot_position - source;
        strncpy(destination, source, base_length);
        destination[base_length] = '\0'; // Null terminate the string
        strcat(destination, ".");
        strcat(destination, new_extension);
    }

    // Copy the file to the new name with the updated extension
    copyFile(source, destination);
    printf("File extension changed successfully from %s to %s\n", source, destination);
}

int main() {
    int choice;
    char source[100], destination[100], new_extension[10];
    do {
        printf("\nFile Management System\n");
        printf("1. Copy File\n");
        printf("2. Move File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Change File Extension\n");
        printf("6. Exit\n");
        printf("0. ClearScreen\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            system("cls");
            break;
        case 1:
            printf("------------------------------------------------\n");
            printf("Enter source file name: ");
            scanf("%s", source);
            printf("Enter destination file name: ");
            scanf("%s", destination);
            copyFile(source, destination);
            break;

        case 2:
            printf("------------------------------------------------\n");
            printf("Enter file name to move: ");
            scanf("%s", source);
            printf("Enter destination: ");
            scanf("%s", destination);
            moveFile(source, destination);
            break;

        case 3:
            printf("------------------------------------------------\n");
            printf("Enter file name to delete: ");
            scanf("%s", source);
            deleteFile(source);
            break;

        case 4:
            printf("------------------------------------------------\n");
            printf("Enter file name to search: ");
            scanf("%s", source);
            searchFile(source);
            break;

        case 5:
            printf("------------------------------------------------\n");
            printf("Enter source file name: ");
            scanf("%s", source);
            printf("Enter new file extension (e.g., txt, csv): ");
            scanf("%s", new_extension);
            changeFileExtension(source, new_extension);
            break;

        case 6:
            printf("------------------------------------------------\n");
            printf("Exiting program\n");
            break;

        default:
            printf("------------------------------------------------\n");
            printf("Invalid choice\n");
        }
    } while (choice != 6);

    return 0;
}
