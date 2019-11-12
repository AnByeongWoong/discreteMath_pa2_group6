#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"











int main(){

    
    FILE *instream;
    int read=0, size=0;
    char buffer[10];
    char *result;
    int buffer_size=sizeof(char);
    int N=0 ,M=0;

    instream=fopen("/dev/stdin", "r");
    char *pStr;
    int length;

    if( instream != NULL )
	{
		char strTemp[255];
        pStr = fgets( strTemp, sizeof(strTemp), instream );
    }
    //// 리눅스 출력이다름 리눅스때는 없어짐
    // pStr[strlen(pStr)-1] = '\0';
    
    length = getLogicLength(pStr);
    printf("ttttttttttt[%d]\n",length);
    char* Logic = (char*)malloc(sizeof(char)*(length+1)); 
    Logic[length] = '\0';
    textConversion(pStr, length, Logic);
    // char b[] = "(V a1 (~ (V (~ (V a2 a3)) a4)))";
    printf("tttttttttt[%s]\n",Logic);
    Tree tree;
    init(&tree);
    Node *start = (Node*)malloc(sizeof(Node));
    start->parent = tree.root;
    tree.root->lChild = start;
    start->data = Logic;
    // printf("sssc[%s]\n",start->data);
    start->lChild = NULL;
    start->rChild = NULL;
    makeTree(start, Logic);
    printall(tree.root->lChild);
    printf("t\n");
    printall(start);
    Node* notnode;
    char* not="~";
    search(start,not);
    printall(tree.root->lChild);

    //// NFFtoCNF(start);
    // 여기부터 필요 
    NFFtoCNF(tree.root);
    printall(tree.root->lChild);
    printOrder(tree.root->lChild);

    clearNode(tree.root);

    free(Logic);
    return 0;
}