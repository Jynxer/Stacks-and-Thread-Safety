/*
 * BlockingStack.c
 *
 * Fixed-size generic array-based BlockingStack implementation.
 *
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "BlockingStack.h"

/*
 * This functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Stack module interface as documented in BlockingStack.h.
 */

 /*
  * Creates a new BlockingStack for at most max_size void* elements.
  * Returns a pointer to valid BlockingStack* on success and NULL on failure.
  */

BlockingStack *new_BlockingStack(int max_size) {
	BlockingStack *newStack = malloc((2 * sizeof(int)) + sizeof(pthread_mutex_t) + (2 * sizeof(sem_t)) + (max_size * sizeof(void*)));
	newStack->maxSize = max_size;
	newStack->size = 0;
	/*
	pthread_mutex_init(&(newStack->mutex), NULL);
	sem_init(&(newStack->empty), 0, max_size);
	sem_init(&(newStack->full), 0, 0);
	*/
	return newStack; //If this function fails, newStack will contain a null pointer since that will be its value.
}

/*
 * Pushes the given void* element onto this Stack.
 * If the stack is full, the function will block the calling thread until there is space in the stack.
 * Returns false when element is NULL and true on success.
 */

bool BlockingStack_push(BlockingStack* this, void* element) {
	if (element == NULL) {
		return false;
	} else {
		sem_wait(&(this->empty));
		pthread_mutex_lock(&(this->mutex));
		this->array[this->size] = element;
		this->size = this->size + 1;
		pthread_mutex_unlock(&(this->mutex));
		sem_post(&(this->full));
	}
	return true;
}

/*
 * Pops the top element from this Stack.
 * If the stack is empty, the function will block until an element can be popped.
 * Returns the popped void* element.
 */

void* BlockingStack_pop(BlockingStack* this) {
	sem_wait(&(this->full));
	pthread_mutex_lock(&(this->mutex));
	void* elementToBePopped = this->array[this->size - 1];
	this->size = this->size - 1;
	this->array[this->size] = NULL;
	pthread_mutex_unlock(&(this->mutex));
	sem_post(&(this->empty));
	return elementToBePopped;
}

/*
 * Returns the number of elements currently on this Stack.
 */

int BlockingStack_size(BlockingStack* this) {
	return this->size;
}

/*
 * Returns true is this Stack is empty, false otherwise.
 */

bool BlockingStack_isEmpty(BlockingStack* this) {
	if (this->size == 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Clears this Stack returning it to an empty state.
 */

void BlockingStack_clear(BlockingStack* this) {
	while (this->size > 0) {
		this->array[this->size - 1] = NULL;
		this->size = this->size - 1;
	}
}

/*
 * Destroys this Stack by freeing the memory used by the Stack.
 */

void BlockingStack_destroy(BlockingStack* this) {
	free(this);
}
