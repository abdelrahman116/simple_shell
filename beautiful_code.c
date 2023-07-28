/**
 * @file beautiful_code.c
 *
 * A beautiful C code that passes the Betty checks.
 */

#include <stdio.h>

/**
 * Function to calculate the factorial of a number.
 *
 * @param n The number for which factorial needs to be calculated.
 * @return The factorial of the given number.
 */
unsigned int factorial(unsigned int n)
{
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

int main()
{
	unsigned int num = 5;
	unsigned int result = factorial(num);

	printf("Factorial of %d is %u\n", num, result);

	return 0;
}

