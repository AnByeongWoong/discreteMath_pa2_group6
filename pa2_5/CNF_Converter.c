#include<stdio.h>
#include "dblist.h"

int main()
{
    DoublyLinkedList sample ;
    init(&sample) ;

    add(&sample, "p") ;
    add(&sample, "q") ;
    add(&sample, "r") ;
    add(&sample, "d") ;
    add(&sample, "s") ;
    
    print(&sample) ;

    deleteData(&sample,"p");
    deleteData(&sample,"q");
    print(&sample) ;
    
    freeList(&sample);
    return 0;
}