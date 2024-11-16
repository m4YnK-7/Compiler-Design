/*
    ============================================================================
    File: 5_shift_reduce_parser.c
    Description: Takes a string as input and parses it using shift reduce  
                 parser , wtih a defined grammer, i.e.
                 S -> AB
                 A -> aA | a
                 B -> bB | b


    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 16, 2024
    Last Modified: November 17, 2024
    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack structure to hold symbols
typedef struct {
    int top;
    char items[MAX];
} Stack;

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = -1;
}

// Function to push onto the stack
void push(Stack* s, char value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop from the stack
char pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return '\0';
    }
}

// Function to get the top element of the stack
char top(Stack* s) {
    if (s->top >= 0) {
        return s->items[s->top];
    }
    return '\0';
}

// Function to print the stack for debugging
void printStack(Stack* s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%c", s->items[i]);
    }
    printf("\n");
}

int count_s = 0;

// Function to perform reduction based on the grammar rules
int reduce(Stack* s) {
    // Check for B -> bB | b
    if (s->top >= 1 && s->items[s->top] == 'B' && s->items[s->top - 1] == 'b') {
        pop(s);
        pop(s);
        push(s, 'B');
        printf("Reduce: B -> bB\n");
        return 1;
    } else if (s->top >= 0 && s->items[s->top] == 'b') {
        pop(s);
        push(s, 'B');
        printf("Reduce: B -> b\n");
        return 1;
    }

    // Check for A -> aA | a
    if (s->top >= 1 && s->items[s->top] == 'A' && s->items[s->top - 1] == 'a') {
        pop(s);
        pop(s);
        push(s, 'A');
        printf("Reduce: A -> aA\n");
        return 1;
    } else if (s->top >= 0 && s->items[s->top] == 'a') {
        pop(s);
        push(s, 'A');
        printf("Reduce: A -> a\n");
        return 1;
    }

    // Check for S -> AB
    if (s->top >= 1 && s->items[s->top] == 'B' && s->items[s->top - 1] == 'A') {
        pop(s);
        pop(s);
        if (s->top == -1){push(s, 'S');}
        printf("Reduce: S -> AB\n");
        return 1;
    }

    return 0; // No reduction performed
}

// Shift-Reduce Parser function
void parse(char* input) {
    Stack stack;
    initStack(&stack);
    int i = 0;
    int length = strlen(input);

    printf("Parsing input: %s\n", input);
    
    while (i < length) {

        // Shift operation
        printf("Shift: %c\n", input[i]);
        push(&stack, input[i]);
        i++;

        // Try to reduce after each shift
        while (reduce(&stack)) {
            printStack(&stack);
        }
    }

    // Final reductions
    while (reduce(&stack)) {
        printStack(&stack);
    }

    // Check if the stack contains only the start symbol 'S'
    if (stack.top == 0 && top(&stack) == 'S') {
        printf("\nInput accepted\n");
    } else {
        printf("\nInput not accepted\n");
    }
}

// Main function
int main() {
    char input[MAX];
    printf("Enter the input string (a's followed by b's): ");
    scanf("%s", input);
    
    parse(input);
    
    return 0;
}
