#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store employee details
struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

// Function to add employee details to the file
void addEmployee(FILE *filePtr) {
    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.empId);
    getchar();  // To consume the newline character left by scanf

    printf("Enter Employee Name: ");
    fgets(emp.empName, 50, stdin);  // Using fgets to allow spaces in names
    emp.empName[strcspn(emp.empName, "\n")] = '\0';  // Remove newline at the end of name

    printf("Enter Employee Salary: ");
    scanf("%f", &emp.empSalary);

    // Seek to the correct position based on empId (1-indexed)
    fseek(filePtr, (emp.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&emp, sizeof(struct Employee), 1, filePtr);
    printf("Employee added successfully.\n");
}

// Function to display employee details
void displayEmployee(FILE *filePtr) {
    struct Employee emp;
    int empId;

    printf("Enter Employee ID to display: ");
    scanf("%d", &empId);

    // Seek to the correct position based on empId (1-indexed)
    fseek(filePtr, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, filePtr);

    if (emp.empId == 0) {
        printf("Employee not found.\n");
    } else {
        printf("Employee ID: %d\n", emp.empId);
        printf("Employee Name: %s\n", emp.empName);
        printf("Employee Salary: %.2f\n", emp.empSalary);
    }
}

// Function to update employee details
void updateEmployee(FILE *filePtr) {
    struct Employee emp;
    int empId;

    printf("Enter Employee ID to update: ");
    scanf("%d", &empId);

    // Seek to the correct position based on empId (1-indexed)
    fseek(filePtr, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&emp, sizeof(struct Employee), 1, filePtr);

    if (emp.empId == 0) {
        printf("Employee not found.\n");
    } else {
        getchar();  // To consume the newline character left by scanf
        printf("Enter new Employee Name: ");
        fgets(emp.empName, 50, stdin);
        emp.empName[strcspn(emp.empName, "\n")] = '\0';  // Remove newline at the end of name

        printf("Enter new Employee Salary: ");
        scanf("%f", &emp.empSalary);

        // Seek back to the same position and write the updated details
        fseek(filePtr, (empId - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&emp, sizeof(struct Employee), 1, filePtr);
        printf("Employee details updated successfully.\n");
    }
}

int main() {
    FILE *filePtr;
    int choice;

    // Open file in read-write binary mode (rb+)
    filePtr = fopen("employee.dat", "rb+");
    if (filePtr == NULL) {
        // If file doesn't exist, create it in write-read binary mode (wb+)
        filePtr = fopen("employee.dat", "wb+");
        if (filePtr == NULL) {
            printf("Error opening the file.\n");
            return 1;
        }
    }

    // Loop for the menu
    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("3. Update Employee Details\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(filePtr);
                break;
            case 2:
                displayEmployee(filePtr);
                break;
            case 3:
                updateEmployee(filePtr);
                break;
            case 4:
                printf("Exiting the program...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 4);

    fclose(filePtr);
    return 0;
}

