/*
 * TestStack.c
 *
 * Very simple unit test file for Stack functionality.
 *
 */

#include <stdio.h>
#include <stddef.h>
#include "Stack.h"
#include "myassert.h"


#define MAX_STACK_SIZE 20

/*
 * The stack to use during tests
 */
static Stack *stack;

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
	stack = new_Stack(MAX_STACK_SIZE);
	total_count++;
}

/*
 * Teardown function to run after each test
 */
void teardown(){
	Stack_destroy(stack);
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
 * Checks that the Stack constructor returns a non-NULL pointer.
 */
int newStackIsNotNull() {
	assert(stack != NULL);
	return TEST_SUCCESS;
}

/*
 * Checks that the size of an empty stack is 0.
 */
int newStackSizeZero() {
	assert(Stack_size(stack) == 0);
	return TEST_SUCCESS;
}


/*
 * Write more of your own test functions below (such as pushOneElement, pushAndPopOneElement, ...)
 * to help you verify correctness of your Stack
 */

 /*
  * Checks that the push function successfully adds the element to the stack.
  */
	int pushOneElement() {
		int value = 5;
		void* item = &value;
		assert(Stack_push(stack, item) == true);
		return TEST_SUCCESS;
	}

	/*
   * Checks that the pop function successfully pops the element from the stack.
   */
 	int pushAndPopOneElement() {
		int value = 5;
		void* item = &value;
		Stack_push(stack, item);
		assert(Stack_pop(stack) == item);
		return TEST_SUCCESS;
 	}

	/*
   * Checks that the array size properly updates and that Stack_size properly reports this.
   */
 	int sizeIncrease() {
		int valueOne = 5;
		void* itemOne = &valueOne;
		int valueTwo = 9;
		void* itemTwo = &valueTwo;
		Stack_push(stack, itemOne);
		Stack_push(stack, itemTwo);
		assert(Stack_size(stack) == 2);
		return TEST_SUCCESS;
 	}

	/*
   * Checks that the Stack_isEmpty function works properly.
   */
 	int isEmptyReturnsFalseCorrectly() {
		int value = 5;
		void* item = &value;
		Stack_push(stack, item);
		assert(Stack_isEmpty(stack) == false);
		return TEST_SUCCESS;
 	}

	int isEmptyReturnsTrueCorrectly() {
		assert(Stack_isEmpty(stack) == true);
		return TEST_SUCCESS;
 	}

	/*
   * Checks that the Stack_clear function works properly.
   */
 	int stackClearedSuccessfully() {
		int valueOne = 5;
		void* itemOne = &valueOne;
		int valueTwo = 9;
		void* itemTwo = &valueTwo;
		Stack_push(stack, itemOne);
		Stack_push(stack, itemTwo);
		Stack_clear(stack);
		assert(Stack_isEmpty(stack) == true);
		return TEST_SUCCESS;
 	}

	int someTest() {
		int value = 32;
		void* item = &value;
		void* popped = Stack_pop(stack);
		printf("%s\n", popped);
		Stack_push(stack, item);
		assert(Stack_isEmpty(stack) == false);
		return TEST_SUCCESS;
	}

/*
 * Main function for the Stack tests which will run each user-defined test in turn.
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
	runTest(someTest);
	/*
	 * you will have to call runTest on all your test functions above, such as
	 *
	 * runTest(pushOneElement);
	 * runTest(pushAndPopOneElement);
	 *
	 */

	printf("Stack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
