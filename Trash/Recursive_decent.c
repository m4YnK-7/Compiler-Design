#include <stdio.h>

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
    input = "aaabbb";  // Example input (valid string)
    printf("Input: %s\n", input);
    
    if (S() && *input == '\0') {
        printf("The string is valid according to the grammar.\n");
    } else {
        printf("The string is invalid according to the grammar.\n");
    }
    
    return 0;
}
