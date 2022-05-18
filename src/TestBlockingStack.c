/*
 * TestStack.c
 *
 * Very simple unit test file for BlockingStack functionality.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "BlockingStack.h"
#include "myassert.h"

struct argTuple {
	BlockingStack* bStack;
	void* element;
};

#define MAX_STACK_SIZE 20

/*
 * The stack to use during tests
 */
static BlockingStack *stack;

/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test
 */
void setup(){
	stack = new_BlockingStack(MAX_STACK_SIZE);
	total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
	BlockingStack_destroy(stack);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
	setup();

	if (testFunction()) success_count++;

	teardown();
}


/*
 * Two sample user-defined tests included below.
 * You will have to write many more tests.
 *
 * Each test function should return TEST_SUCCESS at the end.
 * Test functions can contain more than one assertion.
 *
 * If any assertion fails, the function name and line number
 * will be printed and the test will return a failure value.
 *
 * You will have to call runTest on your test functions in main below.
 */


/*
 * Checks that the BlockingStack constructor returns a non-NULL pointer.
 */
int newStackIsNotNull() {
	assert(stack != NULL);
	return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty blocking stack is 0.
 */
int newStackSizeZero() {
	assert(BlockingStack_size(stack) == 0);
	return TEST_SUCCESS;
}

/*
 * Write more of your own test functions below (such as pushOneElement, pushAndPopOneElement, ...)
 * to help you verify correctness of your BlockingStack
 */

 /*
  * Checks that the push function successfully adds the element to the stack.
  */
  int pushOneElement() {
 	 int value = 5;
 	 void* item = &value;
 	 assert(BlockingStack_push(stack, item) == true);
 	 return TEST_SUCCESS;
  }

  /*
 	* Checks that the pop function successfully pops the element from the stack.
 	*/
  int pushAndPopOneElement() {
 	 int value = 5;
 	 void* item = &value;
 	 BlockingStack_push(stack, item);
 	 assert(BlockingStack_pop(stack) == item);
 	 return TEST_SUCCESS;
  }

  /*
 	* Checks that the array size properly updates and that BlockingStack_size properly reports this.
 	*/
  int sizeIncrease() {
 	 int valueOne = 5;
 	 void* itemOne = &valueOne;
 	 int valueTwo = 9;
 	 void* itemTwo = &valueTwo;
 	 BlockingStack_push(stack, itemOne);
 	 BlockingStack_push(stack, itemTwo);
 	 assert(BlockingStack_size(stack) == 2);
 	 return TEST_SUCCESS;
  }

  /*
 	* Checks that the BlockingStack_isEmpty function works properly.
 	*/
  int isEmptyReturnsFalseCorrectly() {
 	 int value = 5;
 	 void* item = &value;
 	 BlockingStack_push(stack, item);
 	 assert(BlockingStack_isEmpty(stack) == false);
 	 return TEST_SUCCESS;
  }

  int isEmptyReturnsTrueCorrectly() {
 	 assert(BlockingStack_isEmpty(stack) == true);
 	 return TEST_SUCCESS;
  }

  /*
 	* Checks that the BlockingStack_clear function works properly.
 	*/
  int stackClearedSuccessfully() {
 	 int valueOne = 5;
 	 void* itemOne = &valueOne;
 	 int valueTwo = 9;
 	 void* itemTwo = &valueTwo;
 	 BlockingStack_push(stack, itemOne);
 	 BlockingStack_push(stack, itemTwo);
 	 BlockingStack_clear(stack);
 	 assert(BlockingStack_isEmpty(stack) == true);
 	 return TEST_SUCCESS;
  }

	/*
 	* Checks that the blocking works properly.
 	*/
	void *thread1(void *arg) {
		void* popped = BlockingStack_pop(arg);
		pthread_exit(popped);
	}

  int blockedSuccessfully() {
		pthread_t *threads = malloc(sizeof(pthread_t) * 2);
		int valueOne = 5;
		void* itemOne = &valueOne;
		int valueTwo = 9;
		void* itemTwo = &valueTwo;
		pthread_mutex_init(&(stack->mutex), NULL);
		sem_init(&(stack->empty), 0, stack->maxSize);
		sem_init(&(stack->full), 0, 0);
		//printf("1:%d\n", BlockingStack_size(stack));
		pthread_create(&threads[0], NULL, thread1, stack);
		//printf("2:%d\n", BlockingStack_size(stack));
		pthread_create(&threads[1], NULL, thread1, stack);
		//printf("3:%d\n", BlockingStack_size(stack));
		for (int i = 0; i < 2; i++) {
			pthread_join(threads[i], NULL);
		}
		//printf("4:%d\n", BlockingStack_size(stack));
		BlockingStack_push(stack, itemOne);
		//printf("5:%d\n", BlockingStack_size(stack));
		BlockingStack_push(stack, itemTwo);
		//printf("6:%d\n", BlockingStack_size(stack));
		pthread_mutex_destroy(&(stack->mutex));
    sem_destroy(&(stack->empty));
    sem_destroy(&(stack->full));
		assert(BlockingStack_isEmpty(stack) == true);
		return TEST_SUCCESS;
  }

/*
 * Main function for the BlockingStack tests which will run each user-defined test in turn.
 */

int main() {
	runTest(newStackIsNotNull);
	runTest(newStackSizeZero);
	runTest(pushOneElement);
	runTest(pushAndPopOneElement);
	runTest(sizeIncrease);
	runTest(isEmptyReturnsFalseCorrectly);
	runTest(isEmptyReturnsTrueCorrectly);
	runTest(stackClearedSuccessfully);
	runTest(blockedSuccessfully);
    /*
     * you will have to call runTest on all your test functions above, such as
     *
     * runTest(pushOneElement);
     * runTest(pushAndPopOneElement);
     *
     */

	printf("\nBlockingStack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
