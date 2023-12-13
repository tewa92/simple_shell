#include "shell.h"

/**
 * _strncpy - Copies up to n characters from the source string to
 *	the destination string.
 * @destin: Pointer to the destination string.
 * @srce: Pointer to the source string.
 * @m: Maximum number of characters to copy.
 * Return: Pointer to the destination string.
 */
char *_strncpy(char *destin, char *srce, int m)
{
	int p, t;
	char *c = destin;

	/**
	 * Copy up to m-1 characters from the source to the destination.
	 * Stop copying if the end of the source string is reached.
	 */
	p = 0;
	while (srce[p] != '\0' && p < m - 1)
	{
		destin[p] = srce[p];
		p++;
	}


	/**
	 * If the copied characters are less than m, fill the remaining
	 * space in the destination with null characters.
	 */
	if (p < m)
	{
		t = p;
		while (t < m)
		{
			destin[t] = '\0';
			t++;
		}
	}

	/* Return a pointer to the destination string. */
	return (c);
} /* End of _strncpy function */

/**
 * _strncat - Concatenates up to n characters from the source
 *	string to the destination string.
 * @destin: Pointer to the destination string.
 * @srce: Pointer to the source string.
 * @m: Maximum number of characters to concatenate.
 * Return: Pointer to the destination string.
 */
char *_strncat(char *destin, char *srce, int m)
{
	int p, t;
	char *c = destin;

	/*Find the end of the destination string.*/
	p = 0;
	t = 0;
	while (destin[p] != '\0')
		p++;

	/**
	 * Concatenate up to m characters from the source to the destination.
	 * Stop concatenating if the end of the source string is reached or
	 * the maximum number of characters is reached.
	 */

	while (srce[t] != '\0' && t < m)
	{
		destin[p] = srce[t];
		p++;
		t++;
	}

	/**
	 * If the concatenated characters are less than m, terminate the
	 * destination string after the last concatenated character.
	 */
	if (t < m)
		destin[p] = '\0';

	/* Return a pointer to the destination string. */
	return (c);
} /* End of _strncat function */


/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @x: Pointer to the string.
 * @k: The character to locate.
 * Return: Pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(char *x, char k)
{
	/**
	 * Iterate through the string until the end is reached or the
	 *	character is found.
	 */
	do {
		if (*x == k)
			return (x);
	} while (*x++ != '\0');

	/* Return NULL if the character is not found. */
	return (NULL);
} /* End of _strchr function */
