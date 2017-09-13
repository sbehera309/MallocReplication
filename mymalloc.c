#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

static char myBlock[5000];

Block *List = (void *)myBlock; // Points to the first block

void separate(Block *fitBlock, size_t size){
	Block *temp = (void *)((void *)fitBlock + size + sizeof(Block));

	temp->isFree = 1;
	temp->blockSize = (fitBlock->blockSize) - size - sizeof(Block);
	temp->next = fitBlock->next;

	fitBlock->isFree = 0;
	fitBlock->blockSize = size;
	fitBlock->next = temp;
}

// Uses the First-fit algorithm
void *mymalloc(size_t size){
	Block *current;
	void *end;

	// Checks if the List is empty or not and starts it if it is empty
	if (!(List->blockSize)){
		List->blockSize = 5000 - sizeof(Block);
		List->next = NULL;
		List->isFree = 1;
	}
	current = List;

	// Traverse through the blocks and find the 1st free block
	while (((current->blockSize < size) || (current->isFree == 0)) && (current->next != NULL)){
		current = current->next;
	}

	if (current->blockSize == size){ // The block fits perfectly
		current->isFree = 0;
		end = (void *)(++current);
		return end;
	}
	else if (current->blockSize > (size + sizeof(Block))){ // Needed to split the block in order to allocate
		separate(current, size);
		end = (void *)(++current);
		return end;
	}
	else{
		end = NULL;
		printf("Not enough space is available for MyMalloc.\n");
		return end;
	}
}

void coalesce(){
	Block *current;
	current = List;

	while (current->next != NULL){
		if ((current->isFree) && (current->next->isFree)){
			current->blockSize += (current->next->blockSize) + sizeof(Block);
			current->next = current->next->next;
		}
		current = current->next;
	}
}

void myfree(void *ptr){
	if (((void *)myBlock <= ptr) && (ptr <= (void *)(myBlock + 5000))){
		ptr -= sizeof(Block);
		Block *current = ptr;
		--current;
		current->isFree = 1;
		coalesce();
	}
	else {
		printf("Please provide a valid pointer allocated by MyMalloc.\n");
	}
}

// Testing purposes
/* int main(){
	int *p = (int *)mymalloc(sizeof(int));
	*p = 10;
	int *d = (int *)mymalloc(sizeof(int));
	*d = 1337;

	printf("%p \n", &p);
	printf("%d \n", *p);

	printf("%p \n", &d);
	printf("%d \n", *d);
	
	myfree(p);
	myfree(d);

	printf("%d\n", sizeof(Block));

	return 0;
} */