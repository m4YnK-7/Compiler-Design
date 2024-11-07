#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_POS 1000  // Adjust this as per the need
#define MAX_STACK 100 // Max stack size for parsing

// Node for syntax tree
typedef struct Node {
    char symbol;            // Symbol for the node (like a, b, *, |, etc.)
    bool nullable;          // Indicates if the subexpression rooted at this node can be empty (nullable)
    int firstpos[MAX_POS];   // Array to store first positions
    int lastpos[MAX_POS];    // Array to store last positions
    int followpos[MAX_POS];  // Follow positions for the node
    struct Node* left;      // Left child of the node
    struct Node* right;     // Right child of the node
} Node;

// Stack for building the tree
typedef struct {
    Node* data[MAX_STACK];
    int top;
} Stack;

// Stack operations
void initStack(Stack* s) {
    s->top = -1;
}

bool isStackEmpty(Stack* s) {
    return s->top == -1;
}

bool isStackFull(Stack* s) {
    return s->top == MAX_STACK - 1;
}

void push(Stack* s, Node* value) {
    if (!isStackFull(s)) {
        s->data[++(s->top)] = value;
    }
}

Node* pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->data[(s->top)--];
    }
    return NULL;
}

Node* peek(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->data[s->top];
    }
    return NULL;
}

// Utility functions
void initializeArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

void mergeSets(int *set1, int *set2, int size) {
    for (int i = 0; i < size; i++) {
        set1[i] |= set2[i];
    }
}

// Create a new syntax tree node
Node* createNode(char symbol) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->nullable = false;
    initializeArray(node->firstpos, MAX_POS);
    initializeArray(node->lastpos, MAX_POS);
    initializeArray(node->followpos, MAX_POS);
    node->left = node->right = NULL;
    return node;
}

// Calculate firstpos for the given node
void findFirstPos(Node* node) {
    if (node == NULL) return;

    if (node->symbol == 'a' || node->symbol == 'b') {  // Assuming basic alphabet symbols
        int pos = node->symbol - 'a' + 1;  // Set position as per the symbol's index
        node->firstpos[pos] = 1;
    }
    else if (node->symbol == '|') {
        findFirstPos(node->left);
        findFirstPos(node->right);
        mergeSets(node->firstpos, node->left->firstpos, MAX_POS);
        mergeSets(node->firstpos, node->right->firstpos, MAX_POS);
    }
    else if (node->symbol == '.') {  // Concatenation
        findFirstPos(node->left);
        findFirstPos(node->right);
        if (node->left->nullable) {
            mergeSets(node->firstpos, node->left->firstpos, MAX_POS);
            mergeSets(node->firstpos, node->right->firstpos, MAX_POS);
        } else {
            mergeSets(node->firstpos, node->left->firstpos, MAX_POS);
        }
    }
    else if (node->symbol == '*') {
        findFirstPos(node->left);
        mergeSets(node->firstpos, node->left->firstpos, MAX_POS);
    }
}

// Calculate lastpos for the given node
void findLastPos(Node* node) {
    if (node == NULL) return;

    if (node->symbol == 'a' || node->symbol == 'b') {  // Assuming basic alphabet symbols
        int pos = node->symbol - 'a' + 1;
        node->lastpos[pos] = 1;
    }
    else if (node->symbol == '|') {
        findLastPos(node->left);
        findLastPos(node->right);
        mergeSets(node->lastpos, node->left->lastpos, MAX_POS);
        mergeSets(node->lastpos, node->right->lastpos, MAX_POS);
    }
    else if (node->symbol == '.') {
        findLastPos(node->left);
        findLastPos(node->right);
        if (node->right->nullable) {
            mergeSets(node->lastpos, node->left->lastpos, MAX_POS);
            mergeSets(node->lastpos, node->right->lastpos, MAX_POS);
        } else {
            mergeSets(node->lastpos, node->right->lastpos, MAX_POS);
        }
    }
    else if (node->symbol == '*') {
        findLastPos(node->left);
        mergeSets(node->lastpos, node->left->lastpos, MAX_POS);
    }
}

// Calculate followpos for the given node
void findFollowPos(Node* node) {
    if (node == NULL) return;

    if (node->symbol == '.') {
        findFollowPos(node->left);
        findFollowPos(node->right);

        // For each position in lastpos of left child, add followpos to firstpos of right child
        for (int i = 0; i < MAX_POS; i++) {
            if (node->left->lastpos[i]) {
                mergeSets(node->followpos, node->right->firstpos, MAX_POS);
            }
        }
    }
    else if (node->symbol == '*') {
        findFollowPos(node->left);

        // For each position in lastpos of this node, add followpos to firstpos of this node
        for (int i = 0; i < MAX_POS; i++) {
            if (node->lastpos[i]) {
                mergeSets(node->followpos, node->firstpos, MAX_POS);
            }
        }
    }
}

// Helper function to check if the character is an operator
int isOperator(char c) {
    return (c == '*' || c == '|' || c == '.');
}

// Parse RE and build syntax tree using Shunting Yard Algorithm
Node* parseRE(char* re) {
    Stack operandStack;
    Stack operatorStack;
    initStack(&operandStack);
    initStack(&operatorStack);

    for (int i = 0; i < strlen(re); i++) {
        char c = re[i];

        if (c == '(') {
            Node* newNode = createNode(c);
            push(&operatorStack, newNode);
        } else if (c == ')') {
            while (!isStackEmpty(&operatorStack) && peek(&operatorStack)->symbol != '(') {
                Node* operatorNode = pop(&operatorStack);

                if (operatorNode->symbol == '*') {
                    operatorNode->left = pop(&operandStack);
                } else {
                    operatorNode->right = pop(&operandStack);
                    operatorNode->left = pop(&operandStack);
                }
                push(&operandStack, operatorNode);
            }
            pop(&operatorStack); // Remove '(' from stack
        } else if (isOperator(c)) {
            Node* newNode = createNode(c);
            while (!isStackEmpty(&operatorStack) && peek(&operatorStack)->symbol != '(') {
                Node* operatorNode = pop(&operatorStack);
                if (operatorNode->symbol == '*') {
                    operatorNode->left = pop(&operandStack);
                } else {
                    operatorNode->right = pop(&operandStack);
                    operatorNode->left = pop(&operandStack);
                }
                push(&operandStack, operatorNode);
            }
            push(&operatorStack, newNode);
        } else {
            // Operand (a, b, etc.)
            Node* newNode = createNode(c);
            push(&operandStack, newNode);
        }
    }

    while (!isStackEmpty(&operatorStack)) {
        Node* operatorNode = pop(&operatorStack);
        if (operatorNode->symbol == '*') {
            operatorNode->left = pop(&operandStack);
        } else {
            operatorNode->right = pop(&operandStack);
            operatorNode->left = pop(&operandStack);
        }
        push(&operandStack, operatorNode);
    }

    return pop(&operandStack);
}

int main() {
    // Input Regular Expression (e.g. "a.b*|c")
    char re[MAX_STACK];
    printf("Enter a regular expression: ");
    scanf("%s", re);

    Node* syntaxTree = parseRE(re);

    // Calculate firstpos, lastpos, and followpos
    findFirstPos(syntaxTree);
    findLastPos(syntaxTree);
    findFollowPos(syntaxTree);

    // Example of accessing followpos, firstpos, lastpos
    printf("FirstPos: ");
    for (int i = 0; i < MAX_POS; i++) {
        if (syntaxTree->firstpos[i])
            printf("%d ", i);
    }
    printf("\n");

    printf("LastPos: ");
    for (int i = 0; i < MAX_POS; i++) {
        if (syntaxTree->lastpos[i])
            printf("%d ", i);
    }
    printf("\n");

    printf("FollowPos: ");
    for (int i = 0; i < MAX_POS; i++) {
        if (syntaxTree->followpos[i])
            printf("%d ", i);
    }
    printf("\n");

    return 0;
}
