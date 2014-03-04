/***
 * Van Mai Nguyen Thi <vn4720@bard.edu>
 * Sep 2013
 * CMSC328: Embedded Operating Systems
 *
 * bmalloc: test program
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "bmem.h"


int main2() {
    int *list;
    
    list = (int*) bmalloc (33554000);
    print_free_list();
    
    list = (int*) bmalloc (700);
    print_free_list();
    
    return 0;
}

int main() {
    int *list, *list2, *list3, *list4, *list5, *list6;
    
    list = (int*) bmalloc (100);
    print_free_list();
    
    list2 = (int*) bmalloc(17);
    print_free_list();
    
    list3 = (int*) bmalloc(100);
    print_free_list();
    
    bfree(list);
    print_free_list();
    
    list4 = (int*) bmalloc(4);
    print_free_list();
    
    bfree(list3);
    print_free_list();
    
    list5 = (int*) bmalloc(97);
    print_free_list();

    list6 = (int*) bmalloc(81);
    print_free_list();
    
    bfree(list5);
    print_free_list();
    bfree(list2);
    print_free_list();
    
    return 0;
}