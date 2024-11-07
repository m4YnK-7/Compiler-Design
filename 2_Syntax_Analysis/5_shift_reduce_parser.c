#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Stack to hold the states
typedef struct {
    int top;
    int items[MAX];
} Stack;

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = -1;
}

// Function to push to the stack
void push(Stack* s, int value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}

// Function to pop from the stack
int pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}

// Function to get the top element of the stack
int top(Stack* s) {
    if (s->top >= 0) {
        return s->items[s->top];
    }
    return -1;
}

// Function to perform the shift operation
void shift(Stack* stateStack, char input, int* currentState) {
    push(stateStack, *currentState);
    (*currentState)++; // Move to the next state (this would depend on the transition table)
    printf("Shift: %c\n", input);
}

// Function to perform the reduce operation
void reduce(Stack* stateStack, char* production) {
    // Simulate the reduce operation by popping states
    printf("Reduce by: %s\n", production);
    // Example: If production is A → a, we would pop states according to grammar rules
    // Here we pop 1 state for production A → a
    pop(stateStack);
}

// Function to parse the input string
void parse(char* input) {
    Stack stateStack;
    initStack(&stateStack);
    
    int currentState = 0; // Initial state
    int inputLength = strlen(input);
    int i = 0; // Index for input string

    while (i < inputLength) {
        char currentInput = input[i];

        // Shift operation
        shift(&stateStack, currentInput, &currentState);
        i++; // Move to the next character in the input

        // Check for reductions (this example assumes a simple scenario)
        if (currentState == 3) { // Assuming state 3 is where we can reduce S → AB
            reduce(&stateStack, "S → AB");
            currentState = 0; // Reset to initial state after reduction
        }
    }

    // Final check for acceptance
    if (top(&stateStack) == 0) { // If the stack is empty, the input is accepted
        printf("22BCE2387\nInput accepted\n");
    } else {
        printf("22BCE2387\naInput not accepted\n");
    }
}

// Main function
int main() {
    char input[MAX];

    printf("Enter the input string (a's and b's only): ");
    scanf("%s", input);

    parse(input);

    return 0;
}
