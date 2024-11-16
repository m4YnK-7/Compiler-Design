/*
    ============================================================================
    File: 6_predictive_parser.c
    Description: Takes a string as input and parses it using Predictive  
                 parser , wtih a defined grammer, i.e.
                 E -> TX
                 X -> X → T+X | e
                 T → FY
                 Y → *FY | e
                 F → (E) | id           

    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 16, 2024
    Last Modified: November 17, 2024
    ============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define MAX_INPUT_SIZE 100

// Stack implementation
char stack[MAX_STACK_SIZE];
int top = -1;

void push(char symbol) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Stack overflow.\n");
        exit(1);
    }
    stack[++top] = symbol;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow.\n");
        exit(1);
    }
    return stack[top--];
}

char peek() {
    if (top == -1) return '\0';
    return stack[top];
}

// Parsing table for new grammar
char parseTable[5][6][10] = {
    {"TX", "", "", "TX", "", ""},  // E → TX
    {"", "+TX", "", "", "e", "e"},  // X → +TX | e
    {"FY", "", "", "FY", "", ""},  // T → FY
    {"", "e", "*FY", "", "e", "e"}, // Y → *FY | e
    {"id", "", "", "(E)", "", ""}    // F → (E) | id
};

// Map terminals to table columns
int getColumn(char terminal) {
    switch (terminal) {
        case 'i': return 0; // id
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

// Map non-terminals to table rows
int getRow(char nonTerminal) {
    switch (nonTerminal) {
        case 'E': return 0;
        case 'X': return 1;
        case 'T': return 2;
        case 'Y': return 3;
        case 'F': return 4;
        default: return -1;
    }
}

// Predictive parser function
void predictiveParse(const char* input) {
    int inputIndex = 0;
    char lookahead = input[inputIndex];

    push('$'); // End of stack marker
    push('E'); // Start symbol

    printf("Stack\tInput\tAction\n");

    while (peek() != '$') {
        char topSymbol = peek();
        printf("%s\t%s\t", stack, &input[inputIndex]);

        // Match terminal
        if (topSymbol == lookahead) {
            pop();
            lookahead = input[++inputIndex];
            printf("Match '%c'\n", topSymbol);
        }
        // Expand non-terminal
        else if (topSymbol >= 'A' && topSymbol <= 'Z') {
            int row = getRow(topSymbol);
            int col = getColumn(lookahead);
            const char* rule = (row != -1 && col != -1) ? parseTable[row][col] : NULL;

            if (rule == NULL || strlen(rule) == 0) {
                printf("\nError: No rule for %c with lookahead '%c'\n", topSymbol, lookahead);
                exit(1);
            }

            pop();
            for (int i = strlen(rule) - 1; i >= 0; i--) {
                if (rule[i] != 'e') push(rule[i]); // Don't push epsilon
            }
            printf("Expand '%c' -> %s\n", topSymbol, rule);
        }
        // Error case
        else {
            printf("\nError: Unexpected symbol '%c' at input '%c'\n", topSymbol, lookahead);
            exit(1);
        }
    }

    if (lookahead == '$') {
        printf("Parsing successful.\n");
    } else {
        printf("\nError: Input not fully consumed.\n");
    }
}

// Main function
int main() {
    char input[MAX_INPUT_SIZE];
    printf("Enter input string (end with '$'): ");
    scanf("%s", input);

    // Start parsing
    predictiveParse(input);

    return 0;
}
