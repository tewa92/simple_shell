#include "shell.h"

/**
 * _erratoi - Converts a string to an integer with error handling.
 * @x: Pointer to the string to be converted.
 * Return: The converted integer on success, or -1 on error.
 */
int _erratoi(char *x)
{
	int o = 0;
	unsigned long int result = 0;

	/*
	 * If the string starts with '+', move the pointer one position ahead.
	 * TODO: Investigate why this affects the return value in the main function.
	 */
	if (*x == '+')
		x++;

	/*
	 * Iterate through the characters of the string and
	 *	convert them to an integer.
	 * Return -1 on error (non-digit characters or overflow).
	 */
	for (o = 0; x[o] != '\0'; o++)
	{
		if (x[o] >= '0' && x[o] <= '9')
		{
			result *= 10;
			result += (x[o] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
	}

	/* Return the converted integer on success. */
	return (result);
} /* End of _erratoi function */


/**
* print_error - Prints an error message to the standard error stream.
* @inform: Pointer to a structure (info_t) containing information
*           (Assuming inform has fields like fname, line_count, argv, etc.)
* @estri: Pointer to the string representing the error message.
* Return: No return value.
*/
void print_error(info_t *inform, char *estri)
{
	/*
	 * Output the filename, line number, program name, and the provided
	 *	error message to the standard error stream.
	 */
	_eputs(inform->fname);
	_eputs(": ");
	print_d(inform->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inform->argv[0]);
	_eputs(": ");
	_eputs(estri);
} /* End of print_error function */


/**
* print_d - Prints an integer to the specified file descriptor.
* @input_num: The integer to be printed.
* @filedesc: The file descriptor where the integer will be printed.
* Return: The number of characters printed.
*/
int print_d(int input_num, int filedesc)
{
	int (*__putchar)(char) = _putchar;
	int o, count = 0;
	unsigned int _abs_, current;

	/*
	 * If the file descriptor is STDERR_FILENO, use _eputchar for printing.
	 */
	if (filedesc == STDERR_FILENO)
		__putchar = _eputchar;

	/*
	 * Determine if the number is negative and calculate its absolute value.
	 * Print a '-' for negative numbers and increment the count.
	 */
	if (input_num < 0)
	{
		_abs_ = -input_num;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input_num;
	}
	current = _abs_;

	/*
	 * Iterate through powers of 10 to print each digit of the absolute value.
	 * Increment the count for each digit printed.
	 */
	for (o = 1000000000; o > 1; o /= 10)
	{
		if (_abs_ / o)
		{
			__putchar('0' + current / o);
			count++;
		}
		current %= o;
	}

	/*
	 * Print the last digit and increment the count.
	 */
	__putchar('0' + current);
	count++;

	/* Return the total number of characters printed. */
	return (count);
} /* End of print_d function */


/**
* convert_number - Converts a number to a string representation
*	in the specified radix.
* @number: The number to be converted.
* @radix: The radix for the conversion (e.g., 10 for decimal, 16
*	for hexadecimal).
* @conversion_flags: Flags to control the conversion
*	(CONVERT_UNSIGNED for unsigned, CONVERT_LOWERCASE for lowercase hex).
* Return: Pointer to the converted string.
*/
char *convert_number(long int number, int radix, int conversion_flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *potr;
	unsigned long m = number;

	/*
	 * Check if the number is negative and set the sign accordingly.
	 * If the number is not unsigned and negative, convert its absolute value.
	 */
	if (!(conversion_flags & CONVERT_UNSIGNED) && number < 0)
	{
		m = -number;
		sign = '-';
	}

	/*
	 * Set the array for digits based on the case (lowercase or uppercase).
	 * Initialize the pointer to the end of the buffer.
	 */
	array = conversion_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	potr = &buffer[49];
	*potr = '\0';

	/*
	 * Perform the conversion by repeatedly dividing the number by the radix and
	 * storing the remainder as a character in the buffer.
	 */
	do {
		*--potr = array[n % radix];
		m /= radix;
	} while (m != 0);

	/*
	 * If the number was negative, prepend the sign character to the result.
	 * Return a pointer to the converted string.
	 */
	if (sign)
		*--potr = sign;

	return (potr);
} /* End of convert_number function */


/**
* remove_comments - Removes comments from a string.
* @buff: Pointer to the string to be processed.
* Return: No return value.
*/
void remove_comments(char *buff)
{
	int o;

	/*
	 * Iterate through the characters of the string.
	 * If a '#' is found and it is either the first character or preceded
	 *	by a space, replace it with a null character and break out of
	 *	the loop.
	 */
	for (o = 0; buff[o] != '\0'; o++)
	{
		if (buff[o] == '#' && (!o || buff[o - 1] == ' '))
		{
			buff[o] = '\0';
			break;
		}
	}
} /* End of remove_comments function */
