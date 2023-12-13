#include "shell.h"

/**
 * _eputs - Outputs a string to the standard error stream.
 * @stri: Pointer to the string to be outputted.
 * Return: No return value.
 */
void _eputs(char *stri)
{
	int p = 0;
	/**
	 * Check if the input string is NULL.
	 * If NULL, return without performing any further actions.
	 */
	if (!stri)
		return;

	/**
	 * Iterate through the characters of the string and output each
	 * character to the standard error stream.
	 */
	while (stri[p] != '\0')
	{
		_eputchar(stri[p]);
		p++;
	}
} /* End of _eputs function */


/**
 * _eputchar - Writes a character to the standard error stream with buffering.
 * @k: The character to be written.
 * Return: Always returns 1.
 */
int _eputchar(char k)
{
	static int o;
	static char buf[WRITE_BUF_SIZE];

	/**
	 * If the character is BUF_FLUSH or the buffer is full, write the
	 *	buffer to the standard error stream.
	 * Reset the buffer index to 0.
	 */
	if (k == BUF_FLUSH || o >= WRITE_BUF_SIZE)
	{
		write(2, buf, o);

		o = 0;

	}

	/**
	 * If the character is not BUF_FLUSH, add it to the buffer and
	 *	increment the buffer index.
	 */

	if (k != BUF_FLUSH)
		buf[o++] = k;

	/* Always return 1. */
	return (1);
} /* End of _eputchar function */

/**
 * _putfd - Writes a character to the specified file descriptor with buffering.
 * @k: The character to be written.
 * @filedesc: The file descriptor where the character will be written.
 * Return: Always returns 1.
 */
int _putfd(char k, int filedesc)
{
	static int o;
	static char buf[WRITE_BUF_SIZE];

	/**
	 * If the character is BUF_FLUSH or the buffer is full, write the
	 *	buffer to the specified file descriptor.
	 *	Reset the buffer index to 0.
  */
	if (k == BUF_FLUSH || o >= WRITE_BUF_SIZE)

	{
		write(filedesc, buf, o);
		o = 0;
	}

	/**
	 * If the character is not BUF_FLUSH, add it to the buffer and
	 *	increment the buffer index.
	 */
	if (k != BUF_FLUSH)
		buf[o++] = k;

	/* Always return 1. */
	return (1);
} /* End of _putfd function */


/**
 * _putsfd - Writes a string to the specified file descriptor.
 * @stri: Pointer to the string to be written.
 * @filedesc: The file descriptor where the string will be written.
 * Return: The number of characters written.
 */
int _putsfd(char *stri, int filedesc)
{
	int o = 0;

	/**
	 * Check if the input string is NULL.
	 * If NULL, return 0 without performing any further actions.
	 */
	if (!stri)
		return (0);

  /**
  * Iterate through the characters of the string and use _putfd to
  *	write each character to the specified file descriptor.
  * Increment the count of characters written.
  */

	while (*stri)
	{
		o += _putfd(*stri++, filedesc);
	}

  /* Return the total number of characters written. */
	return (o);
} /* End of _putsfd function */
