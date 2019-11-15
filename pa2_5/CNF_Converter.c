#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

int checkBracket(char* str){
    int i =0;
    int count=0;
    while(i != strlen(str)){
        if(str[i]=='('){
            count++;
        }
        else if(str[i] == ')'){
            count--;
        }
        i++;

    }
    if(count ==0){
        return 1;
    }
    else return -1;
}

int checkOperator(char* str){
    int i =0;
    while(i != strlen(str)-1){
        if(str[i]=='('){
            if(str[i+1]!='n' || str[i+1]!='o' || str[i+1] !='a' ){
                printf("operation error\n");
                return -1;
            }
        }
        
        i++;
    }
    
    return 1;
}

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
	if(checkBracket(pStr)==-1){
		printf("bracket error\n");
	};
    Tree tree;
    init(&tree);
    Node *start = (Node*)malloc(sizeof(Node));
    start->parent = tree.root;
    tree.root->lChild = start;
    start->data = pStr;

    start->lChild = NULL;
    start->rChild = NULL;
    makeTree(start, pStr);

    Node* notnode;
    char* not="~";
    search(start,not);
    NFFtoCNF(tree.root);
    printOrder(tree.root->lChild);

    clearNode(tree.root);

    return 0;
}
