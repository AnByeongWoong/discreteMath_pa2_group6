#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

int main(){

    

    // char b[] = "(V a1 (~ (V (~ (V a2 a3)) a4)))";
    // char b[] = "(V a1 (n (V a2 a3)) ~a4)";
    // char b[] = "(V (~ (n a1 a5)) (~ (V (~ (V a2 a3)) a4)))";
    char b[] = "(V a1 (n (V a2 a3) a4))";
    Tree tree;
    init(&tree);
    (tree.root)->data = b;
    makeTree(tree.root, b);
    // printall(tree.root);

    // char* not ="~";
    // search(tree.root,not);
    // printf("after search\n");
    // printall(tree.root);
    NFFtoCNF(&tree);
    // printall(tree.root);
    // Node* newNode=(Node*)malloc(sizeof(Node));
    // newNode->parent = tree.root;
    // makeCopyNode(tree.root->rChild, newNode);
    // printf("t\n");
    // printall(newNode);
    
    

    
    // Node* newNode=(Node*)malloc(sizeof(Node));
    // newNode->parent = tree.root;
    // printf("after copy\n");

    // makeCopyNode(tree.root->rChild, newNode);
    
    // printall(newNode);

    clearNode(tree.root);

    
    //     char b[] = "(V (~ (n a1 a5)) (~ (V (~ (V a2 a3)) a4)))";


    // Tree tree;
    // init(&tree);
    // (tree.root)->data = b;
    // makeTree(tree.root, b);
    
    // printall(tree.root);
    // Node* notnode;
    // char* not="~";
    // search(tree.root,not);
    // // if(notnode==NULL) break;
    // // notCalculator(notnode->lChild,notnode);
    // // notCalculator(notnode->rChild,notnode);
    // //deleteNode(notnode,notnode->parent);
    // printall(tree.root);
    // clearNode(tree.root);
    // // free(inputLogic);
    // return 0;

    return 0;
}