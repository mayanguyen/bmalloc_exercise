/***
 * Van Mai Nguyen Thi <vn4720@bard.edu>
 * Sep 2013
 * CMSC328: Embedded Operating Systems
 *
 * bmalloc: Dynamic Memory Management
 *
 */

#include "bmem.h"
#include <stdio.h>

#define align4(x) (((((x) - 1) >> 2) << 2) + 4)

typedef struct block {
    size_t size;
    struct block* next;
    struct block* prev;
    int free; // 0 means not free, 1 means free.
} block_t;

static char heap[MAX_HEAP_SIZE];
static block_t* freelist = 0;


void report_space_usage() {
    block_t* space;
    int m_free = MAX_HEAP_SIZE;
    int m_used = 0;
    int m_record = 0;
    
    if (!freelist) {
        printf("The total heap size is %d and the heap is not used.\n", MAX_HEAP_SIZE);
        return;
    }
    
    for (space = freelist; space != NULL; space = space->next) {
        if (space->free==0) {
            m_free -= (int) space->size;
            m_used += (int) space->size;
        }
        else {
            m_free -= (int) sizeof(block_t);
            m_used += (int) sizeof(block_t);
        }
        m_record += (int) sizeof(block_t);
    }
    
    printf("%s \t %s \t %s \t %s\n",
           "heap size", "mem free", "mem used", "mem for record keeping");
    printf("--------------------------------------");
    printf("--------------------------------------\n");
    printf("%d \t %d \t %d \t %d\n",
           MAX_HEAP_SIZE, m_free, m_used, m_record);
    printf("%d%% \t\t %f%% \t %f%% \t %f%%\n",
           100, ((100*(double)m_free)/MAX_HEAP_SIZE), ((100*(double)m_used)/MAX_HEAP_SIZE), ((100*(double)m_record)/MAX_HEAP_SIZE));
    
    printf("--------------------------------------");
    printf("--------------------------------------\n");
}


void print_freelist(){
    block_t* space;
    
    if (!freelist) return;
    
    printf("%s \t\t %s \t\t %s \t\t %s \t %s\n",
           "addr", "prev", "next", "free", "size");
    printf("--------------------------------------");
    printf("--------------------------------------\n");
    for (space = freelist; space != NULL; space = space->next){{
        printf("%08ld \t n:%08ld \t p:%08ld \t %d \t %zu\n",
               space - freelist,
               space->prev ? space->prev - freelist : 0,
               space->next ? space->next - freelist : 0,
               space->free, space->size);
    }
    }
    printf("--------------------------------------");
    printf("--------------------------------------\n");
}

void print_free_list(){
    block_t* space;
    printf("%s \t\t %s \t\t %s \t\t %s \t %s\n",
           "addr", "prev", "next", "free", "size");
    printf("--------------------------------------");    printf("--------------------------------------\n");
    for (space = freelist; space != NULL; space = space->next){{
        printf("%012ld \t %012ld \t %012ld \t %d \t %zu\n",
               space, space->prev, space->next, space->free, space->size);}}
    printf("--------------------------------------");
    printf("--------------------------------------\n");
}

void* bmalloc(size_t size){
    block_t* block = (block_t*) heap;
    block_t* block_next;
    size_t new_size = align4( size + sizeof(block_t) );
//    printf("\nCreate block of size %zu. \n", new_size);     //TEST: uncomment this.

    
    if (freelist == 0) {
        freelist = (block_t*) heap;
        block->size = MAX_HEAP_SIZE;
        block->next = 0;
        block->prev = 0;
        block->free = 1;
    }
    else {
        while ((block->free==0 || (block->size < new_size)) ) {
            if (block->next==0) {
                printf("Could not create block. Heap is full.\n");
                return 0;
            }
            block = block->next;
        }
    }
    
    
    if ( block->size > new_size + sizeof(block_t) ) {
        block_next = (void*) block + new_size;
        block_next->size = block->size - new_size;
        block_next->next = block->next;
        block_next->prev = (void*) block;
        block_next->free = 1;
        if (block_next->next !=0)
            block_next->next->prev = (void*) block_next;
        
        block->size = new_size;
        block->next = (void*) block_next;
    }
    
    block->free = 0;
    
    return (void*)block + sizeof(block_t);
}

void bfree(void* ptr){
    block_t* block = ptr - sizeof(block_t);
    block_t* block2 = (block_t*) block;
    size_t new_size = block->size;

    printf("\nFree block at address %08ld, of size %08ld. \nPreceding block is %08ld. \n", block-freelist, block->size, block->prev);    //TEST: uncomment this.

    print_free_list();
    
    if (block2->next!=0 && block2->next->free!=0) {
        block2 = block2->next;
        new_size = new_size + (block2->size);
    }
    
    if (block->prev!=0 && block->prev->free!=0) {
        block = block->prev;
        new_size = new_size + (block->size);
    }
    
    block->free = 1;
    block->size = new_size;
    block->next = block2->next;
 
    print_free_list();
}

