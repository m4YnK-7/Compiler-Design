/*
Will take time
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct TreeNode{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(char data){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct TreeNode* createTree(const char *str){
    int n = strlen(str);

    struct TreeNode* root = createNode('.');
    struct TreeNode* current = root;
    
    root->data = '.';
    root->right = createNode('#');

    for(int i=n-1;i>0;i--){
        if(str[i]=='a' || str[i]=='b'){
            current->left = createNode('.');
            struct TreeNode* newNode = createNode(str[i]);
            current = current->left;

            current->right = newNode;
        }
    }
    current->left = createNode(str[0]);

    return root;
}

void printTree(struct TreeNode *root) {
    if (root == NULL) return;
    printTree(root->left);
    printf("%c ", root->data);
    printTree(root->right);
}




int main(){
    const char *re = "bb#"; // Sample regular expression
    struct TreeNode *syntaxTree = createTree(re);

    // Print the tree to verify (in-order)
    printf("In-order traversal of the syntax tree:\n");
    printTree(syntaxTree);


    return 0;
}