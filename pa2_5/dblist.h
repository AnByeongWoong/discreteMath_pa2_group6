#ifndef __DBLIST_H__
#define __DBLIST_H__

#define TRUE 1
#define FALSE 0

typedef struct _node{
    struct _node *parent;
    struct _node *left;
    struct _node *right;
    char* data;
}Node;

typedef struct _list{
    Node *head;
}DoublyLinkedList;

void init (DoublyLinkedList*);
void add (DoublyLinkedList*,char*);
void print(DoublyLinkedList*);
int search(DoublyLinkedList*,char*);
void deleteData(DoublyLinkedList*, char*);
void freeList(DoublyLinkedList*);
void moveList(DoublyLinkedList*);

#endif