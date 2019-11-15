#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

void init (Tree* plist){
    

    Node *dummy = (Node*)malloc(sizeof(Node));
    
    dummy -> parent= NULL;
    dummy ->data = NULL;
    dummy -> rChild = NULL;
    dummy -> lChild = NULL;
    plist -> root= dummy;
}

void lAdd (Node*current,char* newData){

    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->data=newData;
   
    newNode->lChild=newNode->rChild=NULL;
    
    newNode->parent = current;
    
    current->lChild=newNode;

}
void rAdd (Node*current,char* newData){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->data=newData;
    newNode->lChild=newNode->rChild=NULL;
    newNode->parent = current;
    current->rChild=newNode;

}

void search(Node*plist,char* sdata){
    Node *find=NULL;
    if(plist==NULL) return;
    if(strcmp(plist->data,sdata)==0){
        notCalculator(plist->lChild,plist);
        notCalculator(plist->rChild,plist);
        deleteNode(plist,plist->parent);
        return;
    }
    search(plist->lChild,sdata);
    search(plist->rChild,sdata);
    // return find;
}
void notCalculator(Node* notNode,Node* parentNode){
    char not[4]="~";
    if(notNode==NULL) return;
    
    if(strcmp(notNode->data,"V")==0) notNode->data="n";
    else if(strcmp(notNode->data,"n")==0) notNode->data="V";
    else if(strcmp(notNode->data,"~")==0) 
    {
        deleteNode(notNode,parentNode);
        return;
    }
    else if(notNode->data[0]=='~'){
       int i=0;
       while(1){
           if(notNode->data[i]=='\0') break;
           notNode->data[i]=notNode->data[i+1];
           i++;
       }
    }
    else{//숫자일때 앞에 not을 붙여서 바꾼다.

    //여기가 문제였었음
     strcat(not,notNode->data);

     notNode->data=(char*)malloc(strlen(notNode->data)+2);
     strcpy(notNode->data,not);

     
    }
    notCalculator(notNode->lChild,notNode);//왼쪽 child랑 오른쪽 child도 동일하게 적용한다.
    notCalculator(notNode->rChild,notNode);
    return;


}
void deleteNode(Node* plist,Node* parentNode){
    char* not="~";
    if(plist->rChild==NULL){//한쪽이 아예 없으면 그냥 올려붙이면됨
        if(parentNode->rChild==plist) {
            parentNode->rChild=plist->lChild;
        }
        else if(parentNode->lChild==plist){
            parentNode->lChild=plist->lChild;
        } 
        plist->lChild->parent=parentNode;
        free(plist);
        return;
  
    }
    else if(plist->lChild==NULL){
        if(parentNode->rChild==plist) 
        {
            parentNode->rChild=plist->rChild;
             
        }else if(parentNode->lChild==plist){
             parentNode->lChild=plist->rChild;
          
        }
        plist->rChild->parent=parentNode;
        free(plist);
        return;
    }
}
void clearNode(Node* t) {
    if(t->lChild!=NULL) clearNode(t->lChild);
    if(t->rChild!=NULL) clearNode(t->rChild);
    t->lChild = NULL;
    t->rChild = NULL;
    free(t);
}

void print(Node* plist){
    if(plist==NULL) return;
    printf("%s\n",plist->data);
}
void printall(Node* t){
    if(t==NULL) return;
    if(t->parent != NULL){
        printf("parent data: [%s]",t->parent->data);
    }
    printf("tree data :[%s]\n",t->data);
    printall(t->lChild);
    printall(t->rChild);
}
void NFFtoCNF(Node* root){
    int num=0;
    Node* t = root->lChild;
    while(1){
        t = root->lChild;
        num=checkTheorder(t);
        if(num!=0)checker(t);
        else break;
    }
}
void checker(Node* plist){
    if(plist==NULL) return;
    if(strcmp(plist->data,"V")==0){
        if(strcmp(plist->lChild->data,"n")==0){
         changer(plist,plist->lChild,0);
         return;   
        }
        else if(strcmp(plist->rChild->data,"n")==0){
        
        changer(plist,plist->rChild,1);
    
         return;
        }
    }
    checker(plist->lChild);
    checker(plist->rChild);
}
int checkTheorder(Node*plist){
    if(plist==NULL) return 0;
    if(strcmp(plist->data,"V")==0){
        if(strcmp(plist->lChild->data,"n")==0){
         return 1;   
        }
        else if(strcmp(plist->rChild->data,"n")==0){
         return 1;
        }
    }
    int num1=checkTheorder(plist->lChild);
    int num2=checkTheorder(plist->rChild);
    if(num1+num2==0) return 0;
    else return 1;
}
int DimensionAndChange(char* text){
    int garoCount = 0;
    int countDirection=0;
    for(int k=0; k<strlen(text); k++){
        while(text[k] !=' ' ){
            if(text[k] == '('){
                garoCount++;
            }
            else if(text[k] == ')'){
                garoCount--;
            }
            if(k==strlen(text)-1){
                break;
            }
            k++;
        }
        if(garoCount==0){
            if(text[k] == ' '){
                text[k] = 'M';
            }
            countDirection++;
        }
    }
    return countDirection;
}

void dimensionMore(Node* treeNode, char* operator, char* elements,int dimensionCount){
    rAdd(treeNode, operator);
    treeNode = treeNode->rChild;
    if(dimensionCount==4){
        lAdd(treeNode, elements);
        
        elements = strtok(NULL,"M");
        rAdd(treeNode, elements);
         makeTree(treeNode->lChild, treeNode->lChild->data);
        makeTree(treeNode->rChild, treeNode->rChild->data);
        return;
    }
    else{
        lAdd(treeNode, elements);
        elements = strtok(NULL,"M");
        dimensionMore(treeNode, operator,elements,dimensionCount-1 );
    }
    makeTree(treeNode->lChild,treeNode->lChild->data);
    makeTree(treeNode->rChild,treeNode->rChild->data);
}

void makeTree(Node* treeNode, char* text){
    char *ptr;
    if(text == NULL){
        return;
    }
    
    

    int dimensionCount = 0;
    if(text[strlen(text)-1] == ')'){
        text[strlen(text)-1] = '\0';
        dimensionCount = DimensionAndChange(&text[1]);
        ptr = strtok(&text[1],"M");
    }
    else{
       ptr = text;
    }
    if(dimensionCount == 0){
        return;
    }
    else if(dimensionCount >3){
        if(strlen(ptr)>1){
            if(strcmp(ptr,"not")==0){
                treeNode->data = "~";        
            }
            else if(strcmp(ptr,"or")==0){
                treeNode->data = "V";        
            }
            else if(strcmp(ptr,"and")==0){
                treeNode->data = "n";        
            }
        }
        else{
            treeNode->data = ptr;
        }
        ptr = strtok(NULL,"M");
        lAdd(treeNode,ptr);    
        ptr = strtok(NULL,"M");
        dimensionMore(treeNode, treeNode->data, ptr, dimensionCount);

    }
    else{
        if(strlen(ptr)>1){
            if(strcmp(ptr,"not")==0){
                treeNode->data = "~";        
            }
            else if(strcmp(ptr,"or")==0){
                treeNode->data = "V";        
            }
            else if(strcmp(ptr,"and")==0){
                treeNode->data = "n";        
            }
        }
        else{
            treeNode->data = ptr;
        }
        ptr = strtok(NULL,"M");
        
        lAdd(treeNode, ptr);
        if(dimensionCount == 2){

            makeTree(treeNode->lChild, treeNode->lChild->data);
            return;
        }

        ptr = strtok(NULL,"M");

        
        rAdd(treeNode, ptr);
    }

    makeTree(treeNode->lChild, treeNode->lChild->data);
    makeTree(treeNode->rChild, treeNode->rChild->data);
}

void makeCopyNode(Node* treeNode, Node* copiedNode){

    if(treeNode == NULL){
        return;
    }
    copiedNode->data = treeNode->data;

    if(treeNode->lChild != NULL){
        
        Node* newNodeLeft=(Node*)malloc(sizeof(Node)); 
        copiedNode->lChild = newNodeLeft; 
        newNodeLeft->parent = copiedNode;
        makeCopyNode(treeNode->lChild, newNodeLeft);
    }
    if(treeNode->rChild != NULL){
        
        Node* newNodeRight=(Node*)malloc(sizeof(Node));   
        copiedNode->rChild = newNodeRight; 
        newNodeRight->parent = copiedNode;
        makeCopyNode(treeNode->rChild, newNodeRight);
    }
    return;
}

void changer(Node*plist,Node*child,int num){


    Node* copyNode=(Node*)malloc(sizeof(Node));
    copyNode->data = plist->data;
    copyNode->parent = NULL;
    copyNode->lChild = NULL;
    copyNode->rChild = NULL;
    if(num==1){
        Node* copyNodeLeft=(Node*)malloc(sizeof(Node));
        copyNodeLeft->parent = NULL;
        copyNodeLeft->rChild = NULL;
        copyNodeLeft->lChild = NULL;

        copyNode->lChild = copyNodeLeft;
        copyNodeLeft->parent = copyNode;
        
        makeCopyNode(plist->lChild,copyNodeLeft);
        if(plist->parent!=NULL){
            if(plist->parent->lChild == plist){
            plist->parent->lChild = child;
            }
            else{
                plist->parent->rChild = child;
            }
        }
        child->parent = plist->parent;    
        plist->rChild = child->rChild;
        child->rChild->parent = plist;
        plist->parent = child;
        copyNode->rChild = child->lChild;
        child->lChild->parent = copyNode;
        child->lChild = plist;
        child->rChild = copyNode;
        copyNode->parent = child;
    }
    else if(num==0){
        Node* copyNodeRight=(Node*)malloc(sizeof(Node));
        copyNodeRight->parent = NULL;
        copyNodeRight->rChild = NULL;
        copyNodeRight->lChild = NULL;

        copyNode->rChild = copyNodeRight;
        copyNodeRight->parent = copyNode;
        
        makeCopyNode(plist->rChild,copyNodeRight);
        if(plist->parent!=NULL){
            if(plist->parent->rChild == plist){
            plist->parent->rChild = child;
            }
            else{
                plist->parent->lChild = child;
            }
        }
        child->parent = plist->parent;
        
        
        plist->lChild = child->rChild;
        child->rChild->parent = plist;

        plist->parent = child;

        copyNode->lChild = child->lChild;
        child->lChild->parent = copyNode;

        child->rChild = plist;

        child->lChild = copyNode;
        copyNode->parent = child;

    }

}

void printOrder(Node* plist){
      if(plist==NULL) return;
    if(strcmp(plist->data,"n")==0){
        printOrder(plist->lChild);
        if(strcmp(plist->lChild->data,"n")!=0) printf("\n");
        printOrder(plist->rChild);
        if(strcmp(plist->rChild->data,"n")!=0) printf("\n");
    }
    else if(strcmp(plist->data,"V")==0){
        printOrder(plist->lChild);
        printOrder(plist->rChild);
    }
    else{
        int num=tokNumber(plist->data);
        printf("%d ",num);
    }

    

}
int tokNumber(char* number){
    char*changeNumber=(char*)malloc(sizeof(char*)*(strlen(number)+1));
    if(number[0]=='~'){
        changeNumber[0]='-';
        for(int i=1;number[i]!='\0';i++){
            changeNumber[i]=number[i+1];
        }
    }
    else{
        for(int i=0;number[i]!='\0';i++){
            changeNumber[i]=number[i+1];
        }
    }
    int num=atoi(changeNumber);
    return num;
}

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

