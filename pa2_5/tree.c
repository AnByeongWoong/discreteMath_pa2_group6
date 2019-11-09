#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

void init (Tree* plist){
    

    Node *dummy = (Node*)malloc(sizeof(Node));
    
    dummy -> parent= NULL;
    dummy ->data = NULL;
    dummy -> rChild = NULL;
    dummy -> lChild = NULL;
    plist -> root= dummy;
    printf("init finish\n");
}

void clearNode(Node* t) {
    //if (t==NULL) return NULL;
    //cout << "your code here\n";
    if(t->lChild!=NULL) clearNode(t->lChild);
    if(t->rChild!=NULL) clearNode(t->rChild);
    t->lChild = NULL;
    t->rChild = NULL;
    free(t);
    //return nullptr;
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
    //// 여기가 아마 strcpy써야 할 수도 있음
    newNode-> data=newData;
    newNode->lChild=newNode->rChild=NULL;
    newNode->parent = current;
    current->rChild=newNode;

}

/*void print(Tree* plist){
    Node *cur = plist ->head->next;
    while(cur !=NULL){
        printf("%s ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
int search(Tree*plist,char* sdata){ 
    Node *cur = plist->head->next;
    while(cur !=NULL){
        if (cur ->data==sdata)
        return TRUE;
        cur =cur->next;
    }
    return FALSE;
}

void deleteData(Tree* plist, char* ddata){
    Node *cur = plist -> head -> next;
    Node *prev = plist -> head;//어떻게 초기화 해도 상관 없음
    while(cur != NULL){
        if (cur ->data == ddata)
            break;
            prev = cur;
            cur = cur->next;
    }
    if (cur == NULL) return;
    prev-> next = cur ->next;
    free(cur);
    return;
}

void freeList(Tree* plist){
    Node *cur = plist -> head;
    Node *prev = NULL;

    while(cur != NULL){
        prev = cur;
        cur =cur->next;
        free(prev);
    }
}


void moveList(Tree*plist){
    Node*cur=plist->head->next->next;
    Node*prev=plist->head->next;
    char* num;
    while(cur !=NULL)
    if(prev->data>cur->data)
    {
        num=prev->data;
        prev->data=cur->data;
        cur->data=num;
        cur=plist->head->next->next;
        prev=plist->head->next;
    }
    else{
        prev=cur;
        cur=cur->next;
    }
}

*/