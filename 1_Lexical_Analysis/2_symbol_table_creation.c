/*
    ==================================================================================
    File: 2_symbol_table_creation.c
    Description:Implements a basic symbol table for a compiler's front-end. 
                This code supports adding and displaying symbol table entries 
                with essential information such as variable name, data type, value, 
                size, and memory address. The current implementation supports "int",
                "float","char","double" and "string" data types and provides error
                handling for unsupported types.

    Author: Mayank Singh
    GitHub: https://github.com/m4YnK-7/Compiler-Design
    Created on: November 13, 2024
    Last Modified: November 13, 2024
    =================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define a structure for a symbol table entry
typedef struct SymbolTableEntry {
    char varName[20];    // Variable Name
    char dataType[10];   // Data Type (e.g., int, float, char, double, string)
    union {              // Value (supports int, float, char, double, and string)
        int iValue;
        float fValue;
        char cValue;
        double dValue;
        char sValue[100];
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
    } 
    else if (strcmp(dataType, "float") == 0) {
        symbolTable[entryCount].value.fValue = *((float *)value);
        symbolTable[entryCount].size = sizeof(float);
        symbolTable[entryCount].address = &symbolTable[entryCount].value.fValue;
    } 
    else if (strcmp(dataType, "char") == 0) {
        symbolTable[entryCount].value.cValue = *((char *)value);
        symbolTable[entryCount].size = sizeof(char);
        symbolTable[entryCount].address = &symbolTable[entryCount].value.cValue;
    } 
    else if (strcmp(dataType, "double") == 0) {
        symbolTable[entryCount].value.dValue = *((double *)value);
        symbolTable[entryCount].size = sizeof(double);
        symbolTable[entryCount].address = &symbolTable[entryCount].value.dValue;
    } 
    else if (strcmp(dataType, "string") == 0) {
        strncpy(symbolTable[entryCount].value.sValue, (char *)value, sizeof(symbolTable[entryCount].value.sValue) - 1);
        symbolTable[entryCount].value.sValue[sizeof(symbolTable[entryCount].value.sValue) - 1] = '\0';
        symbolTable[entryCount].size = strlen(symbolTable[entryCount].value.sValue) + 1;
        symbolTable[entryCount].address = symbolTable[entryCount].value.sValue;
    } 
    else {
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
        } else if (strcmp(symbolTable[i].dataType, "char") == 0) {
            printf("%-10c ", symbolTable[i].value.cValue);
        } else if (strcmp(symbolTable[i].dataType, "double") == 0) {
            printf("%-10.4f ", symbolTable[i].value.dValue);  // 4 decimal places for double
        } else if (strcmp(symbolTable[i].dataType, "string") == 0) {
            printf("%-10s ", symbolTable[i].value.sValue);
        } else {
            printf("%-10s ", "Unknown");  // For any unsupported type
        }

        printf("%-10d %-10p\n", symbolTable[i].size, symbolTable[i].address);
    }
}

int main() {
    int iValue = 10;
    float fValue = 20.5;
    char cValue = 'A';
    double dValue = 50.1234;
    char sValue[] = "Hello!";

    addEntry("x", "int", &iValue);
    addEntry("y", "float", &fValue);
    addEntry("ch", "char", &cValue);
    addEntry("z", "double", &dValue);
    addEntry("msg", "string", sValue);

    displaySymbolTable(); 
    return 0;
}
