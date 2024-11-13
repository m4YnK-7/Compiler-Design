/*
    ============================================================================
    File: 1_optimization_principles.c
    Description: Implements various code optimization techniques such as common
                 subexpression elimination, dead code elimination, and strength 
                 reduction for 3-address code representations.
    
    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 13, 2024
    Last Modified: November 13, 2024
    ============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    char lhs[10];
    char rhs[50];
} ThreeAddressCode;

// Function to eliminate common subexpressions
void eliminateCommonSubexpressions(ThreeAddressCode code[], int *n) {
    printf("\nPerforming Common Subexpression Elimination:\n");
    for (int i = 0; i < *n; i++) {
        for (int j = i + 1; j < *n; j++) {
            if (strcmp(code[i].rhs, code[j].rhs) == 0) {
                printf("Common subexpression found: %s = %s and %s = %s\n", code[i].lhs, code[i].rhs, code[j].lhs, code[j].rhs);
                strcpy(code[j].rhs, code[i].lhs); // Replace the right-hand side with the variable of the first occurrence
            }
        }
    }
}

// Function to eliminate dead code
void eliminateDeadCode(ThreeAddressCode code[], int *n) {
    printf("\nPerforming Dead Code Elimination:\n");
    bool isUsed[MAX] = {false};
    for (int i = 0; i < *n; i++) {
        // Mark all variables that appear on the right-hand side of any statement as "used"
        for (int j = i + 1; j < *n; j++) {
            if (strstr(code[j].rhs, code[i].lhs)) {
                isUsed[i] = true;
                break;
            }
        }
    }
    // Keep all used variables and the last statement by default
    int index = 0;
    for (int i = 0; i < *n; i++) {
        if (isUsed[i] || i == *n - 1) {
            code[index++] = code[i];
        } else {
            printf("Eliminating dead code: %s = %s\n", code[i].lhs, code[i].rhs);
        }
    }
    *n = index; // Update the number of valid statements
}

// Function to perform strength reduction
void applyStrengthReduction(ThreeAddressCode code[], int n) {
    printf("\nApplying Strength Reduction:\n");
    for (int i = 0; i < n; i++) {
        // Perform strength reduction transformations for multiplication and division
        if (strstr(code[i].rhs, "* 2")) {
            char variable[50];
            sscanf(code[i].rhs, "%s * 2", variable);
            printf("Strength reduction: Replacing %s = %s with %s = %s + %s\n", 
                   code[i].lhs, code[i].rhs, code[i].lhs, variable, variable);
            snprintf(code[i].rhs, sizeof(code[i].rhs), "%s + %s", variable, variable);
        } else if (strstr(code[i].rhs, "/ 2")) {
            char variable[50];
            sscanf(code[i].rhs, "%s / 2", variable);
            printf("Strength reduction: Replacing %s = %s with %s = %s >> 1\n", 
                   code[i].lhs, code[i].rhs, code[i].lhs, variable);
            snprintf(code[i].rhs, sizeof(code[i].rhs), "%s >> 1", variable);
        }
    }
}

// Function to print the optimized code
void printOptimizedCode(ThreeAddressCode code[], int n) {
    printf("\nFinal Optimized Code:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].lhs, code[i].rhs);
    }
}

int main() {
    int n;
    ThreeAddressCode code[MAX];

    printf("Enter number of 3-address code statements: ");
    scanf("%d", &n);
    printf("Enter the 3-address code statements (format: LHS = RHS):\n");
    for (int i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        scanf("%s = %[^\n]s", code[i].lhs, code[i].rhs);
    }

    eliminateCommonSubexpressions(code, &n);
    eliminateDeadCode(code, &n);
    applyStrengthReduction(code, n);
    printOptimizedCode(code, n); // Print the final optimized code

    return 0;
}
