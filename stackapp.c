/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string

*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post: returns 1 if the parentheses are balanced, otherwise 0
*/
int isBalanced(char* s)
{
	// Assert that the string passed to the function is a valid pointer
	assert(s != 0);
	// Create a dynamic array with 1 element to start where we can push and pop
	// potential parentheses in the string
	DynArr *parenStack = newDynArr(2);
	// Declare a char variable that will hold the current character in the string
	// as we loop through the full string
  char charToCheck;


	do {
		charToCheck = nextChar(s);

		// If the current character is an opening parenthsis, push it onto the top of
		// the stack.

		if (charToCheck == '(') {
			pushDynArr(parenStack, '(');
		} else if (charToCheck == '{') {
			pushDynArr(parenStack, '{');
		} else if (charToCheck == '[') {
			pushDynArr(parenStack, '[');
		}

		// If the stack is empty and we're looking at a closing parenthesis, return false
		// and free memory before inspecting the top of the stack, since there is no
		// chance of finding a matching opening parenthesis.
		// If the character at the top of the stack is a matching opening parenthesis,
		// pop and continue checking characters, since we can assume that the parentheses
		// match thus far.
		// Finally, return false if there was a different character at the top of the
		// stack, because this suggests the parentheses were closed in the incorrect order
		// and therefore are not balanced.

		if (charToCheck == ')') {
			if (isEmptyDynArr(parenStack)) {
				deleteDynArr(parenStack);
				return 0;
			} else if (topDynArr(parenStack) == '(') {
				popDynArr(parenStack);
			} else {
				deleteDynArr(parenStack);
				return 0;
			}
		} else if (charToCheck == '}') {
			if (isEmptyDynArr(parenStack)) {
				deleteDynArr(parenStack);
				return 0;
			} else if (topDynArr(parenStack) == '{') {
				popDynArr(parenStack);
			} else {
				deleteDynArr(parenStack);
				return 0;
			}
		} else if (charToCheck == ']') {
			if (isEmptyDynArr(parenStack)) {
				deleteDynArr(parenStack);
				return 0;
			} else if (topDynArr(parenStack) == '[') {
				popDynArr(parenStack);
			} else {
				deleteDynArr(parenStack);
				return 0;
			}
		}

	} while(charToCheck != '\0');

	if (isEmptyDynArr(parenStack)) {
		deleteDynArr(parenStack);
		// Return true if our stack is empty after reading the whole string
		return 1;
	} else {
		deleteDynArr(parenStack);
		// Return false if the stack is not empty, as this means that there was a
		// parenthesis that was not closed.
		return 0;
	}

}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}
