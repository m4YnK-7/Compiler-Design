/*
    ============================================================================
    File: 3_elim_left_recursion.c
    Description: Eliminates left recursion from a given grammar.

    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 16, 2024
    Last Modified: November 16, 2024
    ============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

// Function to eliminate left recursion
void eliminateLeftRecursion(char nonTerminal, char productions[MAX][MAX], int productionCount) {
    char alpha[MAX][MAX], beta[MAX][MAX];
    int alphaCount = 0, betaCount = 0;

    // Separate productions into alpha (left-recursive) and beta (non-left-recursive)
    for (int i = 0; i < productionCount; i++) {
        if (productions[i][0] == nonTerminal) {
            strcpy(alpha[alphaCount++], productions[i] + 1); // Remove the left-recursive non-terminal
        } else {
            strcpy(beta[betaCount++], productions[i]);
        }
    }

    // Check if left recursion exists
    if (alphaCount > 0) {
        printf("%c -> ", nonTerminal);
        for (int i = 0; i < betaCount; i++) {
            printf("%s%c'", beta[i], nonTerminal);
            if (i != betaCount - 1) {
                printf(" | ");
            }
        }
        printf("\n");

        printf("%c' -> ", nonTerminal);
        for (int i = 0; i < alphaCount; i++) {
            printf("%s%c'", alpha[i], nonTerminal);
            if (i != alphaCount - 1) {
                printf(" | ");
            }
        }
        printf(" | eps\n");
    } else {
        // If no left recursion, print the original productions
        printf("%c -> ", nonTerminal);
        for (int i = 0; i < productionCount; i++) {
            printf("%s", productions[i]);
            if (i != productionCount - 1) {
                printf(" | ");
            }
        }
        printf("\n");
    }
}

int main() {
    char nonTerminal;
    char productions[MAX][MAX];
    int productionCount;

    printf("Enter the non-terminal: ");
    scanf(" %c", &nonTerminal);

    printf("Enter the number of productions: ");
    scanf("%d", &productionCount);

    printf("Enter the productions (use '|' to separate alternatives if needed):\n");
    for (int i = 0; i < productionCount; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", productions[i]);
    }

    printf("\nGrammar after eliminating left recursion:\n");
    eliminateLeftRecursion(nonTerminal, productions, productionCount);

    return 0;
}
