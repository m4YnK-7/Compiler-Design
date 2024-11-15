/*
    ============================================================================
    File: 4_recursive_decent_parser.c
    Description: Takes a string as input and parses it using recursive decent 
                 parser , wtih a defined grammer, i.e.
                 S -> aSb | ab

    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 16, 2024
    Last Modified: November 16, 2024
    ============================================================================
*/

#include <stdio.h>
#include<stdlib.h>

char *input;  // Input string

// Function prototypes
int S();  // Parse the start symbol

// Function to parse S: S -> aSb | ab
int S() {
    if (*input == 'a') {
        input++;  // Consume 'a'
        if (S()) {  // Recursive call for 'S'
            if (*input == 'b') {
                input++;  // Consume 'b'
                return 1;  // Successfully parsed 'aSb'
            } else {
                printf("Error: Expected 'b'\n");
                return 0;
            }
        }
    } else if (*input == 'b') {
        return 1;  // Successfully parsed 'ab'
    }
    return 0;
}

// Main function
int main() {
    // input = "aaaabbb";  // Example input (valid string)
    input = malloc(100 * sizeof(char));
    // printf("Input: %s\n", input);

    printf("Enter Input: ");
    scanf("%s", input);  // Read input
    
    if (S() && *input == '\0') {
        printf("The string is valid according to the grammar.\n");
    } else {
        printf("The string is invalid according to the grammar.\n");
    }
    
    return 0;
}
