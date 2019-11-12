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
    printf("init finish\n");
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

void search(Node*plist,char* sdata){//not node가 어디에 있는지 찾아보는 sdata에는 not이 들어있음 function
    Node *find=NULL;
    if(plist==NULL) return;
    //printf("aaaaaaaaaaaa\n");
    //printall(plist);

    //printf("far before[%s]?\n",plist->data);
    if(strcmp(plist->data,sdata)==0){
        //printf("before[%s]?\n",plist->data);
        notCalculator(plist->lChild,plist);
        //if(plist->lChild!=NULL) printf("before1[%s]?\n",plist->lChild->data);
        notCalculator(plist->rChild,plist);
        // if(plist->rChild!=NULL) printf("before2[%s]?\n",plist->rChild->data);
        deleteNode(plist,plist->parent);
        return;
    }
    search(plist->lChild,sdata);
    search(plist->rChild,sdata);
    // return find;
}
void notCalculator(Node* notNode,Node* parentNode){//notnode에 처음 찾은 not의 왼쪽 오른쪽을 parmeter로 각각줘서 실행,즉 notcalculator를 두번 실행한다고 보면 됨.
    char not[2]="~";
    if(notNode==NULL) return;
    
    printf("what the[%s]?\n",notNode->data);
    if(strcmp(notNode->data,"V")==0) notNode->data="n";
    else if(strcmp(notNode->data,"n")==0) notNode->data="V";
    else if(strcmp(notNode->data,"~")==0) //처음 not이 아니라 not뒤에 not이 있을때,
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
    //if (t==NULL) return NULL;
    //cout << "your code here\n";
    if(t->lChild!=NULL) clearNode(t->lChild);
    if(t->rChild!=NULL) clearNode(t->rChild);
    t->lChild = NULL;
    t->rChild = NULL;
    free(t);
    //return nullptr;
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
void NFFtoCNF(Tree*t){
    int num=0;
    while(1){
        num=checkTheorder(t->root);
        if(num!=0)checker(t->root);
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
/*
만약 현재 노드가 v면 자식 노드들 중에 n이 있나 체크하고 없으면 각각 자식노드로 내려간다.
그리고 위와 같이 체크 만약 있다면 
분배 법칙으로 한다.
어떻게 분배 법칙으로 하면 
*/

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
    // printf("countDirection: %d\n",countDirection);
    return countDirection;
}

void dimensionMore(Node* treeNode, char* operator, char* elements,int dimensionCount){
    rAdd(treeNode, operator);
    // printf("rAdd ptr: [%s]\n",treeNode->rChild->data);
    treeNode = treeNode->rChild;
    if(dimensionCount==4){
        // printf("ladd: [%s]\n",elements);
        lAdd(treeNode, elements);
        
        elements = strtok(NULL,"M");
        // printf("radd: [%s]\n",elements);
        rAdd(treeNode, elements);
         makeTree(treeNode->lChild, treeNode->lChild->data);
        makeTree(treeNode->rChild, treeNode->rChild->data);
        return;
    }
    else{
        // printf("ladd: [%s]\n",elements);
        lAdd(treeNode, elements);
        makeTree(treeNode->lChild, treeNode->lChild->data);
        elements = strtok(NULL,"M");
        // printf("next layer, dimensionCount = %d\n",dimensionCount);
    }
}

void makeTree(Node* treeNode, char* text){
    char *ptr;
    if(text == NULL){
        printf("text finish\n");
        printf("lastx %s\n",text);
        return;
    }
    
    
    ///// 받아온 () 짜르기
    int dimensionCount = 0;
    if(text[strlen(text)-1] == ')'){
        text[strlen(text)-1] = '\0';
        dimensionCount = DimensionAndChange(&text[1]);
            printf("dimensionCount: [%d]\n",dimensionCount);

        ptr = strtok(&text[1],"M");
    }
    else{
       //data 그냥 써도 됌 
       ptr = text;
    }
    if(dimensionCount == 0){
        return;
    }
    else if(dimensionCount >3){
        treeNode->data = ptr;

        // printf("dimensionCount>3 ptr:[%s]\n",ptr);

        ptr = strtok(NULL,"M");
        lAdd(treeNode,ptr);
        // printf("dimensionCount>3 lchild ptr:[%s]\n",ptr);
        
        ptr = strtok(NULL,"M");
        dimensionMore(treeNode, treeNode->data, ptr, dimensionCount);

    }
    else{
        treeNode->data = ptr;
        // printf("ptr:[%s]\n",ptr);
        ptr = strtok(NULL,"M");
        
        lAdd(treeNode, ptr);
        // printf("lchild:[%s]\n",treeNode->lChild->data);
        if(dimensionCount == 2){
            makeTree(treeNode->lChild, treeNode->lChild->data);
            return;
        }

        ptr = strtok(NULL,"M");

        
        rAdd(treeNode, ptr);
        // printf("rchild:[%s]\n",treeNode->rChild->data);
    }

    makeTree(treeNode->lChild, treeNode->lChild->data);
    makeTree(treeNode->rChild, treeNode->rChild->data);
}

///// Node를 하나 만들고 그것을 보내주기, treeNode를 copiedNode에 복사한다
void makeCopyNode(Node* treeNode, Node* copiedNode){

    // Node* copyNode=(Node*)malloc(sizeof(Node));
    if(treeNode == NULL){
        return;
    }
    copiedNode->data = treeNode->data;
    // printf("dddddd[%s]\n",copiedNode->data);
    if(treeNode->lChild != NULL){
        
        Node* newNodeLeft=(Node*)malloc(sizeof(Node)); 
        // newNodeLeft->rChild = NULL;  
        copiedNode->lChild = newNodeLeft; 
        newNodeLeft->parent = copiedNode;
        makeCopyNode(treeNode->lChild, newNodeLeft);
    }
    if(treeNode->rChild != NULL){
        
        Node* newNodeRight=(Node*)malloc(sizeof(Node));   
        // newNodeRight->lChild = NULL;
        copiedNode->rChild = newNodeRight; 
        newNodeRight->parent = copiedNode;
        makeCopyNode(treeNode->rChild, newNodeRight);
    }
    return;
    /// data를 복사할때 allocate를 해야하는지 아닌지는 나중에 생각해보기
}

// void makeNode(Node* newNode){
//     newNode = (Node*)malloc(sizeof(Node));
//     newNode->parent = NULL;
//     newNode->lChild = NULL;
//     newNode->rChild = NULL;
//     newNode->data = NULL;
//     return;
// }

/// plist 중복될 node , childe 는 바꿀 노드, 
void changer(Node*plist,Node*child,int num){
    Node* copyNode=(Node*)malloc(sizeof(Node));
    copyNode->data = plist->data;
    copyNode->parent = NULL;
    copyNode->lChild = NULL;
    copyNode->rChild = NULL;
    printf("aasdfsdf[%s]\n",child->data);
    if(num==1){//오른쪽꺼랑 바꿔야 될떄
        /*
        먼저 copyNode의 왼쪽 child를 plist의 왼쪽 child와 동일하게 만들고
        data도 plist의 데이터와 동일하게 만든다.
        그리고 child의 노드의 왼쪽 child를 copyNode 오른쪽 child에 연결
        그리고 plist의 오른쪽 노드를 child노드의 오른쪽에 연결
        그리고 child의 왼쪽을 copynode에 연결,child의 오른쪽 노드를 plist에 연결
        plist가 parent의 왼쪽인지 오른쪽인지 알아야 된다.
        */
        //// copy
        

        
        printall(plist);
        printf("ssssssssssss\n");
        Node* copyNodeLeft=(Node*)malloc(sizeof(Node));
        copyNodeLeft->parent = NULL;
        copyNodeLeft->rChild = NULL;
        copyNodeLeft->lChild = NULL;

        copyNode->lChild = copyNodeLeft;
        copyNodeLeft->parent = copyNode;
        
        makeCopyNode(plist->lChild,copyNodeLeft);
        printf("pyeongang\n");
        printall(copyNode);
        printf("pyeongang\n");
        // printf("aa[%s]\n",copyNode->data);
        // printf("aa[%s]\n",copyNode->lChild->data);
        // printf("aa[%s]\n",copyNode->rChild->data);
 
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
        // printall(copyNode);
        copyNode->parent = child;
        printf("lllllllll\n");
        printall(child);
        // printf("child->lchild[%s]\n",child->lChild->data);
        // printf("child->rchild[%s]\n",child->rChild->data);
        // printf("child->lchild->lchild[%s]\n",child->lChild->lChild->data);
        // printf("child->lchild->rchild[%s]\n",child->lChild->rChild->data);
        // printf("child->rchild->lchild[%s]\n",child->rChild->lChild->data);
        // printf("child->rchild->rchild[%s]\n",child->rChild->rChild->data);
        // copyNode->parent = child;
        // copyNode->rChild = child->lChild;
        // child->lChild = plist;
        // plist->rChild = child->rChild;
        // child -> rChild = copyNode;
        // plist ->parent = child;
        
    //    copyNode->lChild=plist->lChild;
    //    copyNode->data=plist->data;
    //    copyNode->rChild=child->lChild;
    //    child->lChild=copyNode;
    //    copyNode->parent=child;
    //    plist->rChild=child->rChild;
    //    child->rChild=plist;
    }
    else if(num==0){//왼쪽꺼랑 바꿀때

        
        Node* copyNodeRight=(Node*)malloc(sizeof(Node));
        copyNodeRight->parent = copyNode;
        makeCopyNode(plist,copyNodeRight);

        copyNode->parent = child;
        copyNode->lChild = child->rChild;
        child->rChild = plist;
        plist->lChild = child->lChild;
        child -> lChild = copyNode;
        plist ->parent = child;

    //    copyNode->rChild=plist->rChild;
    //    copyNode->data=plist->data;
    //    copyNode->lChild=child->lChild;
    //    child->lChild=copyNode;
    //    copyNode->parent=child;
    //    plist->lChild=child->rChild;
    //    child->rChild=plist;

    }

}

void printOrder(Node* plist){
    if(plist==NULL) return;
    if(strcmp(plist->data,"n")==0){
        if(strcmp(plist->lChild->data,"V")!=0&&strcmp(plist->lChild->data,"n")!=0&&(plist->lChild->data != NULL)){
            int num=tokNumber(plist->lChild->data);
            printf("%d\n",num);
        }
        if(strcmp(plist->rChild->data,"V")!=0&&strcmp(plist->rChild->data,"n")!=0&&(plist->rChild->data != NULL)){
            int num=tokNumber(plist->rChild->data);
            printf("%d\n",num);
        }
    }
    else if(strcmp(plist->data,"V")==0&&strcmp(plist->parent->data,"n")!=0){
        if(strcmp(plist->lChild->data,"V")!=0&&(plist->lChild->data != NULL)){
            int num=tokNumber(plist->lChild->data);
            printf("%d ",num);
        }
        if(strcmp(plist->rChild->data,"V")!=0&&(plist->rChild->data != NULL)){
            int num=tokNumber(plist->rChild->data);
            printf("%d ",num);
        }
    }
    else if(strcmp(plist->data,"V")==0&&strcmp(plist->parent->data,"n")==0){
        printf("\n");
        if(strcmp(plist->lChild->data,"V")!=0&&(plist->lChild->data != NULL)){
           int num=tokNumber(plist->lChild->data);
           printf("%d ",num);
        }
        if(strcmp(plist->rChild->data,"V")!=0&&(plist->rChild->data != NULL)){
            int num=tokNumber(plist->rChild->data);
            printf("%d ",num);
        }
    }
    printOrder(plist->lChild);
    printOrder(plist->rChild);
}
int tokNumber(char* number){
    /*받은거에서 맨앞에가 ~가 있는지 판단하고
    있으면, 첫번째 인덱스에 - 집어넣고, number인덱스 3번째부터 \0전까지 받는다.
    없으면, number에 두번째 인덱스 부터 \0전까지 받는다.
    받은 것을 숫자로 바꿈 그리고 보내줌*/
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
    //printf("%d\n",num);
    return num;
}