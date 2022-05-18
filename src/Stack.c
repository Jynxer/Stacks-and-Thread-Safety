/*
 * Stack.c
 *
 * Fixed-size generic array-based Stack implementation.
 *
 */

#include <stddef.h>
#include <stdlib.h>
#include "Stack.h"


/*
 * This functions below all return default values and don't work.
 * You will need to provide a correct implementation of the Stack module interface as documented in Stack.h.
 */

 /*
  * Creates a new Stack for at most max_size void* elements.
  * Returns a pointer to valid Stack* on success and NULL on failure.
  */

Stack *new_Stack(int max_size) {
	Stack *newStack = malloc((2 * sizeof(int)) + (max_size * sizeof(void*)));
	newStack->maxSize = max_size;
	newStack->size = 0;
	return newStack; //If this function fails, newStack will contain a null pointer since that will be its value.
}

/*
 * Pushes the given void* element onto this Stack.
 * Returns true on success and false on push failure when element is NULL or stack is full.
 */

bool Stack_push(Stack* this, void* element) {
	if (this->size == this->maxSize) {
		return false;
	} else if (element == NULL) {
		return false;
	} else {
		this->array[this->size] = element;
		this->size = this->size + 1;
	}
	return true;
}

/*
 * Pops the top element from this Stack.
 * Returns popped void* element on success or NULL if stack is empty.
 */

void* Stack_pop(Stack* this) {
	if (this->size == 0) {
		return NULL;
	} else {
		void* elementToBePopped = this->array[this->size - 1];
		this->size = this->size - 1;
		this->array[this->size] = NULL;
		return elementToBePopped;
	}
}

/*
 * Returns the number of elements currently on this Stack.
 */

int Stack_size(Stack* this) {
	return this->size;
}

/*
 * Returns true is this Stack is empty, false otherwise.
 */

bool Stack_isEmpty(Stack* this) {
	if (this->size == 0) {
		return true;
	} else {
		return false;
	}
}

/*
 * Clears this Stack returning it to an empty state.
 */

void Stack_clear(Stack* this) {
	while (this->size > 0) {
		this->array[this->size - 1] = NULL;
		this->size = this->size - 1;
	}
}

/*
 * Destroys this Stack by freeing the memory used by the Stack.
 */

void Stack_destroy(Stack* this) {
	free(this);
}
