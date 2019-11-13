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
    while(i != strlen(str)){
        if(str[i]=='V' || str[i] == 'n' || str[i] == '~' ){
            if(str[i-1]!='('){
                return -1;
            }
        }
        
        i++;
    }
    
    return 1;
}

char *replaceWord(char *s, const char *oldW, const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
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

    // length = getLogicLength(pStr);
    // char* Logic = (char*)malloc(sizeof(char)*(length+1)); 
    // Logic[length] = '\0';
    // textConversion(pStr, length, Logic);
    // // char* Logic = replaceWord(pStr, "(not", "(~");
    // // Logic = replaceWord(Logic, "(or", "(V");
    // // Logic = replaceWord(Logic, "(and", "(n");
    // if(checkBracket(Logic)==-1){
    //     printf("syntax error!! check bracket\n");
    //     return 0;
    // }
    // if(checkOperator(Logic)==-1){
    //     printf("syntax error!! check operator\n");
    //     return 0;
    // }
    // printf("tttttttttt[%s]\n",Logic);
    Tree tree;
    init(&tree);
    Node *start = (Node*)malloc(sizeof(Node));
    start->parent = tree.root;
    tree.root->lChild = start;
    start->data = pStr;

    start->lChild = NULL;
    start->rChild = NULL;
    makeTree(start, pStr);
    printall(tree.root->lChild);
    
    Node* notnode;
    char* not="~";
    search(start,not);
    // printall(tree.root->lChild);
    NFFtoCNF(tree.root);
    // printall(tree.root->lChild);
    printOrder(tree.root->lChild);

    clearNode(tree.root);

    // free(Logic);
    return 0;
}