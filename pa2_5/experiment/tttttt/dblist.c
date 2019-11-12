#include<stdio.h>
#include<stdlib.h>
#include "dblist.h"

void init (DoublyLinkedList*plist){
    Node *dummy = (Node*)malloc(sizeof(Node));
    dummy -> next= NULL;
    
    plist -> head= dummy;
}

void add (DoublyLinkedList*plist,char* newData){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode-> data=newData;
    newNode->next=NULL;

    Node *cur= plist->head;
    while(cur->next !=NULL)
        cur = cur->next;

    cur->next = newNode;
    newNode ->prev=cur;

}

void print(DoublyLinkedList* plist){
    Node *cur = plist ->head->next;
    while(cur !=NULL){
        printf("%s ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
int search(DoublyLinkedList*plist,char* sdata){ 
    Node *cur = plist->head->next;
    while(cur !=NULL){
        if (cur ->data==sdata)
        return TRUE;
        cur =cur->next;
    }
    return FALSE;
}

void deleteData(DoublyLinkedList* plist, char* ddata){
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

void freeList(DoublyLinkedList* plist){
    Node *cur = plist -> head;
    Node *prev = NULL;

    while(cur != NULL){
        prev = cur;
        cur =cur->next;
        free(prev);
    }
}


void moveList(DoublyLinkedList*plist){
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

