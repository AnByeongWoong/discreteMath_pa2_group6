#ifndef __TREE_H__
#define __TREE_H__

#define TRUE 1
#define FALSE 0

typedef struct _node{
    struct _node *parent;
    struct _node *lChild;
    struct _node *rChild;
    char* data;
}Node;

typedef struct _list{
    Node *root;
}Tree;

void makeTree(Node* , char*);
void dimensionMore(Node*, char*, char*, int );
int DimensionAndChange(char*);
void init (Tree*);
void lAdd (Node*,char*);
void rAdd (Node*,char*);
void print(Node*);
void search(Node*,char*);
void deleteNode(Node*,Node*);
void freeList(Tree*);
void moveList(Tree*);
void clearNode(Node* t);
void printall(Node*);
void notCalculator(Node* ,Node*);
int checkTheorder(Node*);
void changer(Node*,Node*,int);
void checker(Node*);
void NFFtoCNF(Node*);
void printOrder(Node*);
int tokNumber(char* );
#endif