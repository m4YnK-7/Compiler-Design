#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SymbolTableEntry{
    int index;
    char dataType[20];
    char varName[100];

    union {
        int ivalue;
        float fvalue;
    } values;

    int size;
    void *address;
} SymbolTableEntry;

#define MAX_SIZE 100

int count=0;
SymbolTableEntry SymbolTable[MAX_SIZE];

void addEntry(char* varName,char* dataType,void *value){
    if (count >= MAX_SIZE) {
        printf("Symbol table is full.\n");
        return;
    }
    SymbolTable[count].index = count;
    strcpy(SymbolTable[count].varName,varName);

    
    

}