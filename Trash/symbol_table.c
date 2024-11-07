#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for a symbol table entry
typedef struct SymbolTableEntry {
    char varName[20];    // Variable Name
    char dataType[10];   // Data Type (e.g., int, float)
    union {              // Value (supports int and float)
        int iValue;
        float fValue;
    } value;
    int size;            // Size of the variable in bytes
    void *address;       // Address of the variable
} SymbolTableEntry;

// Define the maximum number of entries
#define MAX_ENTRIES 100

SymbolTableEntry symbolTable[MAX_ENTRIES]; // Symbol Table array
int entryCount = 0; // Number of entries in the symbol table

// Function to add a new entry to the symbol table
void addEntry(char *varName, char *dataType, void *value) {
        if (entryCount >= MAX_ENTRIES) {
            printf("Symbol table is full.\n");
            return;
        }

    // Set the variable name and data type
    strcpy(symbolTable[entryCount].varName, varName);
    strcpy(symbolTable[entryCount].dataType, dataType);

    // Set the value and calculate the size based on data type
    if (strcmp(dataType, "int") == 0) {
        symbolTable[entryCount].value.iValue = *((int *)value);
        symbolTable[entryCount].size = sizeof(int);
        symbolTable[entryCount].address = &symbolTable[entryCount].value.iValue;
    } else if (strcmp(dataType, "float") == 0) {
        symbolTable[entryCount].value.fValue = *((float *)value);
        symbolTable[entryCount].size = sizeof(float);
        symbolTable[entryCount].address = &symbolTable[entryCount].value.fValue;
    } else {
        printf("Unsupported data type.\n");
        return;
    }

    entryCount++;
}

// Function to display the symbol table
void displaySymbolTable() {
    printf("\n%-15s %-10s %-10s %-10s %-10s\n", "Var Name", "Data Type", "Value", "Size", "Address");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%-15s %-10s ", symbolTable[i].varName, symbolTable[i].dataType);
        
        if (strcmp(symbolTable[i].dataType, "int") == 0) {
            printf("%-10d ", symbolTable[i].value.iValue);
        } else if (strcmp(symbolTable[i].dataType, "float") == 0) {
            printf("%-10.2f ", symbolTable[i].value.fValue);
        }

        printf("%-10d %-10p\n", symbolTable[i].size, symbolTable[i].address);
    }
}

int main() {
    int iValue = 10;
    float fValue = 20.5;

    addEntry("x", "int", &iValue);
    addEntry("y", "float", &fValue);

    displaySymbolTable();
    return 0;
}
