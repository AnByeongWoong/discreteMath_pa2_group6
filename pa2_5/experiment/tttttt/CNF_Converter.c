#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

#define BUFFERSIZE 1



void putText(Node* treeNode, char* text, int goParentsCount ){
    
    if(text == NULL){
        printf("text finish\n");
        printf("lastx %s\n",text);
        return;
    }
    if(goParentsCount != 0){
        printf("go to parents\n");
        putText(treeNode->parent, text, goParentsCount-1 );
        return;
    }
    
    // printf("[putTEXT]%s\n",&text[1]);
    ////// 처음 값 setting 완료? 여기 이상
    // printf("first if \n");
    if(treeNode->data == NULL){
        // printf("when tree %s\n",&text[1]);
        treeNode->data = &text[1] ;
        
        // strcpy(treeNode->data,&text[1]);
        text = strtok(NULL," ");
        printf("data init %s\n",treeNode->data);
    
    }
   
    // printf("second if \n");

    if(treeNode->rChild ==NULL && text[0] == '('){
        // printf("aaaaa\n");
        rAdd(treeNode,&text[1]);
        
        printf("data right %s\n",treeNode->rChild->data);
        text = strtok(NULL," ");
        putText(treeNode->rChild,text,goParentsCount);
    }
    // else if(text[strlen(text)-1]==')'){
    //     // printf("bbbb\n");
    //     ///위로 한칸 올라가기
    //     printf("tt\n");
    //     text[strlen(text)-1] = '\0';
    //     printf("aa\n");
    //     putText(treeNode->parent, text);
    // }
    else if(treeNode->lChild == NULL && text[0] != '(' && text[strlen(text)-1]!=')'){
        
        // printf("마지막이여기?");
        lAdd(treeNode, text);
        text = strtok(NULL," ");
        printf("data left %s\n",treeNode->lChild->data);
        putText(treeNode, text,goParentsCount);
    }
    // else if(treeNode->lChild != NULL && text[0] != '(' && text[strlen(text)-1]==')'){
    else if( text[0] != '(' && text[strlen(text)-1]==')'){
        // printf("left f right make\n");
        int i =1;
        
        while(text[strlen(text)-i] == ')'){
          
            goParentsCount++;
            text[strlen(text)-1] = '\0';
            // printf("text: %s\n",text);
            
        }
        if(treeNode->lChild == NULL){
            lAdd(treeNode,text);
            printf("data left %s\n",treeNode->lChild->data);
            printf("%s\n",text);
            printf("%d\n",goParentsCount);
        }
        else{
            rAdd(treeNode, text);
            printf("data right %s\n",treeNode->rChild->data);
        }
        
        text = strtok(NULL," ");
        printf("after strtok : %s\n",text);
        // text = strtok(NULL," ");
        
        putText(treeNode, text,goParentsCount);
    }

}


int main(){

    // FILE *instream;
    // int read=0, size=0;
    // char buffer[10];
    // char *result;
    // int buffer_size=sizeof(char)*BUFFERSIZE;
    // int N=0 ,M=0;

    // instream=fopen("/dev/stdin", "r");
    
    // char * inputLogic = NULL;
    // if( instream != NULL )
	// {
	// 	char strTemp[255];
	// 	char *pStr;
        
        
	// 	while( !feof( instream ) )
	// 	{
	// 		pStr = fgets( strTemp, sizeof(strTemp), instream );
    //         if(pStr == NULL){
    //             continue;
    //         }
    //         char *ptr = strtok(strTemp, " ");
    //         while(ptr != NULL){
    //             if(inputLogic == NULL){
    //                 inputLogic = (char*)malloc(sizeof(char)*strlen(ptr));
    //             }
    //             else{
    //                 if(ptr[0]=='('){
    //                     if(ptr[1]==' '){
    //                         inputLogic = realloc(inputLogic, sizeof(char)*2);    
    //                     }
    //                     else{
    //                         inputLogic = realloc(inputLogic, sizeof(char)*3);
    //                     }
                        
    //                 }
    //                 else{
    //                     inputLogic = realloc(inputLogic, sizeof(char)*(strlen(ptr)+1));
    //                 }
                    
    //             }


    //             if(strcmp(ptr,"(or")==0){
    //                 strcat(inputLogic,"(V ");
    //             }
    //             else if(strcmp(ptr,"(not")==0){
    //                 strcat(inputLogic,"(~ ");
    //             }
    //             else if(strcmp(ptr,"(and")==0){
    //                 strcat(inputLogic,"(n ");
    //             }
    //             else if(strcmp(ptr,"( ")==0){
    //                 strcat(inputLogic,"( ");
    //             }
    //             else{
                    
    //                 strcat(inputLogic,ptr);
    //                 strcat(inputLogic," ");
    //             }
                
               
    //             ptr = strtok(NULL, " ");
    //         }
    //        printf("%s\n",inputLogic);


            
    //         // char *ptr = strtok(strTemp, " ");
    //         // ptr = strtok(NULL, " ");
           
    //         }
	// }

    // ///////// inputLogic 으로 tree에 넣기 
    // char *inputText;
    // inputText = strtok(inputLogic," ");

    // // printf("length %d\n",strlen(inputLogic));
    // // printf("%s \n",inputLogic);
    // // printf("aaaaa%c",inputLogic[31]);
    

    char a[32] = "(V a1 (~ (V (~ (V a2 a3)) a4)))";
    printf("%s\n",a);
    char *inputText;
    inputText = strtok(a," ");
    Tree tree;
    
    init(&tree);
    putText(tree.root, inputText, 0);
    // clearNode((&tree)->root);
    
    // if(tree.root->lChild->rChild->data == NULL){
    //     printf("ttt");
    // }
    // printf("node: %s\n",tree.root->lChild->rChild->data);
    // printf("node: %s\n",tree.root->rChild->data);
    // printf("node: %s\n",tree.root->rChild->rChild->data);
    // printf("node: %s\n",tree.root->rChild->rChild->lChild->data);
    // printf("node: %s\n",tree.root->rChild->rChild->lChild->lChild->data);
    //     printf("node: %s\n",tree.root->rChild->rChild->data);
    printall(tree.root);
    
    clearNode(tree.root);
    // free(inputLogic);
    return 0;
}