/*
    ============================================================================
    File: 1_3address_codes.c
    Description:
    Generates table form representation of three-address codes in 3 different
    form quadruples,triples and indirect triples from the given 3-address code.
    
    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 16, 2024
    Last Modified: November 16, 2024
    ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structures for the three forms of TAC
typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

typedef struct {
    char op[10];
    char arg1[10];
    char arg2[10];
} Triple;

typedef struct {
    int index; // Reference to the triple index
} IndirectTriple;

// Example exprsn (e.g., a = b + c)
typedef struct {
    char result[10];
    char arg1[10];
    char op[10];
    char arg2[10];
} Expression;

Expression exprsn[MAX];
int expCount = 0; 

// Function to parse a single expression from a line of input
void parseExpression(const char* line) {
    char result[10], arg1[10], op[10], arg2[10];

    // Parse the line into components
    sscanf(line, " %s = %s %s %s", result, arg1, op, arg2);

    // Store the parsed components in the global array
    strcpy(exprsn[expCount].result, result);
    strcpy(exprsn[expCount].arg1, arg1);
    strcpy(exprsn[expCount].op, op);
    strcpy(exprsn[expCount].arg2, arg2);

    // Increment the expression Count
    expCount++;
}

// Function to generate quadruples
void generateQuadruples(Expression exprsn[], Quadruple quads[]) {
    for (int i = 0; i < expCount; i++) {
        strcpy(quads[i].op, exprsn[i].op);
        strcpy(quads[i].arg1, exprsn[i].arg1);
        strcpy(quads[i].arg2, exprsn[i].arg2);
        strcpy(quads[i].result, exprsn[i].result);
    }
}

// Function to generate triples
void generateTriples(Expression exprsn[], Triple triples[]) {
    for (int i = 0; i < expCount; i++) {
        strcpy(triples[i].op, exprsn[i].op);
        strcpy(triples[i].arg1, exprsn[i].arg1);
        strcpy(triples[i].arg2, exprsn[i].arg2);
    }
}

// Function to generate indirect tri    ples
void generateIndirectTriples(IndirectTriple indirectTriples[]) {
    for (int i = 0; i < expCount; i++) {
        indirectTriples[i].index = i; // Referencing the triples
    }
}

// Display Quadruples
void displayQuadruples(Quadruple quads[]) {
    printf("\nQuadruples:\n");
    printf("Index\tOp\tArg1\tArg2\tResult\n");
    for (int i = 0; i < expCount; i++) {
        printf("%d\t%s\t%s\t%s\t%s\n", i, quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result);
    }
}

// Display Triples
void displayTriples(Triple triples[]) {
    printf("\nTriples:\n");
    printf("Index\tOp\tArg1\tArg2\n");
    for (int i = 0; i < expCount; i++) {
        printf("%d\t%s\t%s\t%s\n", i, triples[i].op, triples[i].arg1, triples[i].arg2);
    }
}

// Display Indirect Triples
void displayIndirectTriples(IndirectTriple indirectTriples[]) {
    printf("\nIndirect Triples:\n");
    printf("Index\tReference\n");
    for (int i = 0; i < expCount; i++) {
        printf("%d\t%d\n", i, indirectTriples[i].index);
    }
}

int main() {
    int numexp;

    printf("Enter the number of exprsn: ");
    scanf("%d", &numexp);
    getchar(); 
    printf("Enter each expression in the format: result = arg1 op arg2\n");

    for (int i = 0; i < numexp; i++) {
        char line[MAX];
        printf("Expression %d: ", i + 1);
        fgets(line, MAX, stdin);
        
        line[strcspn(line, "\n")] = 0;
        parseExpression(line);
    }    

    Quadruple quads[MAX];
    generateQuadruples(exprsn, quads);
    displayQuadruples(quads);

    Triple triples[MAX];
    generateTriples(exprsn, triples);
    displayTriples(triples);

    IndirectTriple indirectTriples[MAX];
    generateIndirectTriples(indirectTriples);
    displayIndirectTriples(indirectTriples);

    return 0;
}