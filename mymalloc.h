#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <stddef.h>

struct block {
	struct block *next; // Points to the next memory block (either allocated or free)
	size_t blockSize; //  Size of the Block that will be allocated
	int isFree; // Should only be 0 if not free and 1 if it is free
};
typedef struct block Block;

/* This function separates a block into
   two blocks for when malloc-ing memory */
void separate(Block *fitBlock, size_t size);

/* This is the mymalloc function that returns a pointer
   to an allocated space for a specific block size */
void *mymalloc(size_t size);

/* This function combines two consecutive blocks that
   are free and combines them into one block with the
   block size being the sum of the original two blocks */
void coalesce();

/* This is the free function that removes the allocated
   block from the list and coalesces any free blocks */
void myfree(void *ptr);

//int main();

#endif //MYMALLOC_H