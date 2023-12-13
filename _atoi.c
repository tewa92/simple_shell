#include "shell.h"

/**
 * interactive - Function Checks if the standard input is associated
 *	with a terminal and if the read file descriptor is less than or equal to 2.
 * @inform: Pointer to a structure (info_t) containing information
 *	(Assuming info has a field named readfd)
 * Return: 1 if the conditions are met, 0 otherwise.
 */
int interactive(info_t *inform)
{
    /**
     * Check if the standard input (file descriptor 0)
     *		is associated with a terminal (interactive input)
     * and if the read file descriptor (assuming info->readfd)
     *		is less than or equal to 2 (commonly stdin, stdout, stderr).
     */
	return (isatty(STDIN_FILENO) && inform->readfd <= 2);
} /* End of interactive function */


/**
 * is_delim - Function Checks if a given character is a delimiter
 *	by comparing it to a set of delimiter characters.
 * @k: The character to be checked.
 * @delimit: Pointer to a string containing delimiter characters.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char k, char *delim)
{
    /* Iterate through the delimiter string */
	while (*delim)
	/**
	 * Check if the current character in the delimiter
	 * string matches the given character
	 */
		if (*delim++ == k)
		return (1);

    /* If the character is not found in the delimiter string, return 0 */
	return (0);
} /* End of is_delim function */


/**
 * _isalpha - Function Checks if a given character is an alphabetic character.
 * @l: The character to be checked.
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int _isalpha(int l)
{
    /**
     * Check if the character is within the range of lowercase or
     * uppercase alphabets
     */
	if ((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))
		return (1);
	else
		return (0);
} /* End of _isalpha function */


/**
 * _atoi - Function Converts a string of digits to an integer.
 * @s: The input string to be converted.
 * Return: the converted integer value.
 */
int _atoi(char *s)
{
    /* Initialize variables */
	int e, sign = 1, flag = 0, output;
	unsigned int result = 0;

    /**
     * Iterate through the characters in the input string until
     * a null character or flag equals 2
     */
	for (e = 0; s[e] != '\0' && flag != 2; e++)
	{
	/* Check for the sign of the number */
		if (s[e] == '-')
			sign *= -1;

	/* Check if the character is a digit */
		if (s[e] >= '0' && s[e] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[e] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

    /* Apply the sign to the result to get the final output */
	if (sign == -1)
		output = -result;
	else
		output = result;

    /* Return the final output */
	return (output);
} /* End of _atoi function */
