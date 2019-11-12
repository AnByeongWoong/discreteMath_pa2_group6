#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "xxtree.h"

int getLogicLength(char* pStr){

    int length=0;
    length= length+2;
    int i=0;
            while(i != strlen(pStr)-2){
                if(pStr[i]=='n' && pStr[i+1]=='o' && pStr[i+2]=='t'){
                    length++;
                    i = i+3;
                }
                else if(pStr[i]=='a' && pStr[i+1]=='n' && pStr[i+2]=='d'){
                    length++;
                    i = i+3;
                }
                else if(pStr[i]=='o' && pStr[i+1]=='r'){
                    length++;
                    i = i+2;
                }
                else{
                    length++;
                    i++;
                }
                
            }
    return length;
}

void textConversion(char* pStr, int length, char* Logic ){
    int i=0;
    int k =0;
    while(i!=length){
        if(k<strlen(pStr)-2){
            if(pStr[k]=='n' && pStr[k+1]=='o' && pStr[k+2]=='t'){
                Logic[i]='~';
                // printf("Logic[%s]\n",Logic);
                k = k+3;
            }
            else if(pStr[k]=='a' && pStr[k+1]=='n' && pStr[k+2]=='d'){
                Logic[i]='n';
                k = k+3;
            }
            else if(pStr[k]=='o' && pStr[k+1]=='r'){
                Logic[i]='V';
                k = k+2;
            }
            else{
                Logic[i]=pStr[k];
                k++;
                
            }
        }
        else{
            Logic[i]=pStr[k];
                k++;
        }
        i++;        
    }
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