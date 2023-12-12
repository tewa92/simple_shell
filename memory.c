#include "shell.h"

/**
 * bfree - Frees memory and sets the pointer to NULL.
 * @potr: Pointer to a pointer to be freed.
 *
 * This function frees the memory pointed to by the given pointer and sets the
 * pointer to NULL.
 *
 * Return: 1 if the memory was freed, 0 if the pointer is NULL.
 */
int bfree(void **potr)
{
	if (potr && *potr)
	{
		free(*potr);
		*potr = NULL;
		return (1);
	}
	return (0);
}
