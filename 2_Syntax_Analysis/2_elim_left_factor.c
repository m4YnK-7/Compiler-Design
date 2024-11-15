/*
    ============================================================================
    File: 2_elim_left_factor.c
    Description: Eliminates left factoring from a given grammer.

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

// Function to eliminate left factoring
void eliminateLeftFactoring(char nonTerminal, char productions[MAX][MAX], int productionCount) {
    char commonPrefix[MAX] = "";
    int prefixLength = 0;

    // Find the common prefix among all productions
    for (int i = 0; i < strlen(productions[0]); i++) {
        char currentChar = productions[0][i];
        int isCommon = 1;

        for (int j = 1; j < productionCount; j++) {
            if (productions[j][i] != currentChar) {
                isCommon = 0;
                break;
            }
        }

        if (isCommon) {
            commonPrefix[prefixLength++] = currentChar;
        } else {
            break;
        }
    }

    commonPrefix[prefixLength] = '\0';

    // Print the factored productions
    if (strlen(commonPrefix) > 0) {
        printf("%c -> %s%c'\n", nonTerminal, commonPrefix, nonTerminal);
        printf("%c' -> ", nonTerminal);

        for (int i = 0; i < productionCount; i++) {
            if (strncmp(productions[i], commonPrefix, prefixLength) == 0) {
                if (productions[i][prefixLength] == '\0') {
                    printf("ε");
                } else {
                    printf("%s", productions[i] + prefixLength);
                }

                if (i != productionCount - 1) {
                    printf(" | ");
                }
            }
        }
        printf("\n");
    } else {
        // If no common prefix, print the original productions
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

    printf("\nGrammar after eliminating left factoring:\n");
    eliminateLeftFactoring(nonTerminal, productions, productionCount);

    return 0;
}
