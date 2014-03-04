/***
 * Keith O'Hara <kohara@bard.edu>
 * Sep 2013
 * CMSC328: Embedded Operating Systems
 * 
 * bmalloc: Dynamic Memory Management
 * 
 */

#ifndef _BMEM_H
#define _BMEM_H

#include <stdlib.h>

#define MAX_HEAP_SIZE (2<<24)

void* bmalloc(size_t size);
void bfree(void* ptr);

#endif /* _BMEM_H */
