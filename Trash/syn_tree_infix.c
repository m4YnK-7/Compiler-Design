#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack structure for operators
typedef struct Stack {
    char data;
    struct Stack* next;
} Stack;

// Tree structure for expression nodes
typedef struct Node {
    char data;           // Operator or operand
    struct Node* left;   // Left child
    struct Node* right;  // Right child
} Node;

// Stack functions for operators
Stack* push(Stack* top, char c) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = c;
    newNode->next = top;
    return newNode;
}

Stack* pop(Stack* top) {
    if (top == NULL) return NULL;
    Stack* temp = top;
    top = top->next;
    free(temp);
    return top;
}

char peek(Stack* top) {
    if (top == NULL) return '\0';
    return top->data;
}

int isEmpty(Stack* top) {
    return top == NULL;
}

// Function to create a new tree node
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to check if the character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');/
}

// Function to get precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix to postfix using Shunting Yard Algorithm
int infixToPostfix(char* infix, char* postfix) {
    Stack* operatorStack = NULL;
    int k = 0;  // Index for postfix expression

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        // If the character is an operand, add it to the output (postfix)
        if (isalnum(c)) {
            postfix[k++] = c;
        }
        // If the character is an operator
        else if (isOperator(c)) {
            while (!isEmpty(operatorStack) && precedence(peek(operatorStack)) >= precedence(c)) {
                postfix[k++] = peek(operatorStack);
                operatorStack = pop(operatorStack);
            }
            operatorStack = push(operatorStack, c);
        }
    }

    // Pop all remaining operators from the stack
    while (!isEmpty(operatorStack)) {
        postfix[k++] = peek(operatorStack);
        operatorStack = pop(operatorStack);
    }
    postfix[k] = '\0';  // Null-terminate the postfix expression

    return 1;
}

// Function to build the syntax tree from postfix expression
Node* buildTreeFromPostfix(char* postfix) {
    Node* stack[100];  // Stack of pointers to Node
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        // If the character is an operand, push it to the stack
        if (isalnum(c)) {
            Node* newNode = createNode(c);
            stack[++top] = newNode;
        }
        // If the character is an operator, pop two nodes, make them children, and push the new tree
        else if (isOperator(c)) {
            Node* newNode = createNode(c);
            newNode->right = stack[top--];
            newNode->left = stack[top--];
            stack[++top] = newNode;
        }
    }

    // The root of the tree is the last element remaining in the stack
    return stack[top];
}

// Function to print the syntax tree in pre-order
void printPreOrder(Node* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Function to print the syntax tree in in-order
void printInOrder(Node* root) {
    if (root == NULL) return;
    printInOrder(root->left);
    printf("%c ", root->data);
    printInOrder(root->right);
}

// Function to print the syntax tree in post-order
void printPostOrder(Node* root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%c ", root->data);
}

int main() {
    char infix[100];   // Buffer to store the input expression
    char postfix[100]; // Buffer to store the postfix expression

    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);  // Read a line of input
    infix[strcspn(infix, "\n")] = 0;     // Remove the newline character

    // Convert the infix expression to postfix
    infixToPostfix(infix, postfix);
    printf("22BCE2387\nPostfix Expression: %s\n", postfix);

    // Build the syntax tree from postfix expression
    Node* root = buildTreeFromPostfix(postfix);

    // Print the syntax tree in pre-order, in-order, and post-order
    printf("Pre-order traversal of the syntax tree: ");
    printPreOrder(root); 
    printf("\n");

    printf("In-order traversal of the syntax tree: ");
    printInOrder(root); 
    printf("\n");

    printf("Post-order traversal of the syntax tree: ");
    printPostOrder(root); 
    printf("\n");

    return 0;
}
