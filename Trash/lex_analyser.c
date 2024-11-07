#include <ctype.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#define MAX_LENGTH 1000 // Increased for larger inputs from a file

// Function to check if a character is a delimiter
bool isDelimiter(char chr){ 
    return (chr == ' ' || chr == '+' || chr == '-'
            || chr == '*' || chr == '/' || chr == ','
            || chr == ';' || chr == '%' || chr == '>'
            || chr == '<' || chr == '=' || chr == '('
            || chr == ')' || chr == '[' || chr == ']'
            || chr == '{' || chr == '}'); 
} 

// Function to check if a character is an operator
bool isOperator(char chr) { 
    return (chr == '+' || chr == '-' || chr == '*'
            || chr == '/' || chr == '>' || chr == '<'
            || chr == '='); 
} 

// Function to check if the string is a valid identifier
bool isValidIdentifier(char* str){ 
    return (str[0] != '0' && str[0] != '1' && str[0] != '2'
            && str[0] != '3' && str[0] != '4'
            && str[0] != '5' && str[0] != '6'
            && str[0] != '7' && str[0] != '8'
            && str[0] != '9' && !isDelimiter(str[0])); 
} 

// Function to check if the string is a keyword
bool isKeyword(char* str) 
{ 
    const char* keywords[] = { 
        "auto", "break", "case", "char", 
        "const", "continue", "default", "do", 
        "double", "else", "enum", "extern", 
        "float", "for", "goto", "if", 
        "int", "long", "register", "return", 
        "short", "signed", "sizeof", "static", 
        "struct", "switch", "typedef", "union", 
        "unsigned", "void", "volatile", "while" 
    }; 
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) { 
        if (strcmp(str, keywords[i]) == 0) { 
            return true; 
        } 
    } 
    return false; 
} 

// Function to check if the string is an integer
bool isInteger(char* str) 
{ 
    if (str == NULL || *str == '\0') { 
        return false; 
    } 
    int i = 0; 
    while (isdigit(str[i])) { 
        i++; 
    } 
    return str[i] == '\0'; 
} 

// Function to extract a substring from a given string
char* getSubstring(char* str, int start, int end) 
{ 
    int length = end - start + 1; 
    char* subStr = (char*)malloc((length + 1) * sizeof(char)); 
    strncpy(subStr, str + start, length); 
    subStr[length] = '\0'; 
    return subStr; 
} 

// Lexical Analyzer function to parse the input
void lexicalAnalyzer(char* input) 
{ 
    int left = 0, right = 0; 
    int len = strlen(input); 

    while (right <= len && left <= right) { 
        if (!isDelimiter(input[right])) 
            right++; 

        if (isDelimiter(input[right]) && left == right) { 
            if (isOperator(input[right])) 
                printf("Token: Operator, Value: %c\n", input[right]); 
            right++; 
            left = right; 
        } 
        else if ((isDelimiter(input[right]) && left != right) || (right == len && left != right)) { 
            char* subStr = getSubstring(input, left, right - 1); 

            if (isKeyword(subStr)) 
                printf("Token: Keyword, Value: %s\n", subStr); 
            else if (isInteger(subStr)) 
                printf("Token: Integer, Value: %s\n", subStr); 
            else if (isValidIdentifier(subStr) && !isDelimiter(input[right - 1])) 
                printf("Token: Identifier, Value: %s\n", subStr); 
            else 
                printf("Token: Unidentified, Value: %s\n", subStr); 
            
            free(subStr);
            left = right; 
        } 
    } 
} 

// Main function to read input from a file
int main() 
{ 
    char filename[MAX_LENGTH]; 
    printf("Enter the filename: "); 
    scanf("%s", filename); 

    FILE* file = fopen(filename, "r"); 
    if (file == NULL) { 
        printf("Error: Cannot open file %s\n", filename); 
        return 1; 
    } 

    char input[MAX_LENGTH]; 
    while (fgets(input, MAX_LENGTH, file) != NULL) { 
        printf("Analyzing: %s\n", input); 
        lexicalAnalyzer(input); 
        printf("\n");
    } 

    fclose(file); 
    return 0; 
}
