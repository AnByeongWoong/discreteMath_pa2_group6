#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

void init (Tree*plist){
    Node *dummy = (Node*)malloc(sizeof(Node));
    dummy -> parent= NULL;
    
    plist -> root= dummy;
}

void lAdd (Node*current,char* newData){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode-> data=newData;
    newNode->lChild=newNode->rChild=NULL;
    
    newNode->parent=current;
    current->lChild=newNode;

}
void rAdd (Node*current,char* newData){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode-> data=newData;
    newNode->lChild=newNode->rChild=NULL;
    newNode->parent=current;
    current->rChild=newNode;

}
Node* search(Node*plist,char* sdata){//not node가 어디에 있는지 찾아보는 sdata에는 not이 들어있음 function
    Node *lcur = plist->lChild;//현재 node의 left child를 저장
    Node *rcur = plist->rChild;//현재 node의 right child를 저장
    Node *find=NULL;
    if(lcur !=NULL){
        if (strcmp(lcur ->data,sdata)==0){//left child의 data에 not이 들어있으면
        find=lcur;//find에 not들어 있는 node를 알려주고 find 반환
        return find;
        }
        find=search(lcur->lChild, sdata);//없다면 계속 왼쪽으로 들어가서 찾기
    }
    if(find==NULL){//위에서 못 찾았다면
     if(rcur !=NULL){
        if (strcmp(rcur ->data,sdata)==0){//위와 동일
        find=rcur;
        return find;
        }
        find=search(rcur->rChild, sdata);
        }
    }
    return find;
}
void notCalculator(Node* notNode,Node* parentNode){//notnode에 처음 찾은 not의 왼쪽 오른쪽을 parmeter로 각각줘서 실행,즉 notcalculator를 두번 실행한다고 보면 됨.
    Node* rcur=notNode->rChild;//현재 node의 오른쪽 child
    Node* lcur=notNode->lChild;//현재 node의 왼쪽 child
    char* not="~";
    if(notNode==NULL) return;
    if(strcmp(notNode->data,"V")==0) notNode->data=="n";
    else if(strcmp(notNode->data,"n")==0) notNode->data=="V";
    else if(strcmp(notNode->data,"~")==0) //처음 not이 아니라 not뒤에 not이 있을때,
    {
        deleteNode(notNode,parentNode);
        return;
    }
    else{//숫자일때 앞에 not을 붙여서 바꾼다.
     strcat(not,notNode->data);
     notNode->data=not;
    }
    notCalculator(rcur,notNode);//왼쪽 child랑 오른쪽 child도 동일하게 적용한다.
    notCalculator(lcur,notNode);

}
void deleteNode(Node* plist,Node* parentNode){
    char* not="~";
    if(plist->rChild==NULL){//한쪽이 아예 없으면 그냥 올려붙이면됨
        if(parentNode->rChild->data==plist->data) parentNode->rChild=plist->lChild;
        else if(parentNode->lChild->data==plist->data) parentNode->lChild=plist->lChild;
        plist->lChild->parent=plist->parent;
        free(plist);
    }
    else if(plist->lChild==NULL){
        if(parentNode->rChild->data==plist->data) parentNode->rChild=plist->rChild;
        else if(parentNode->lChild->data==plist->data) parentNode->lChild=plist->rChild;
        plist->rChild->parent=plist->parent;
        free(plist);
    }
    else{/*둘의 선수관계를 확인하고 누가 parent node로 올라갈지 정해야됨
        두개 같을때
        두 개가 다를때
            한쪽이 not일때, 다른 한쪽이 
        */
        if(strcmp(plist->lChild->data,plist->rChild->data)==0){

        }

    }


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
/*void print(Tree* plist){
    Node *cur = plist ->head->next;
    while(cur !=NULL){
        printf("%s ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}
*/


/*


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