#include "shell.h"

/**
 * _memset - Fills the first @n bytes of the memory area pointed to by @s
 *           with the constant byte @b.
 * @dest: Pointer to the destination memory area.
 * @byte: The constant byte to fill the memory area.
 * @count: Number of bytes to fill.
 *
 * This function fills the first @count bytes of the memory area
 *	pointed to by @dest
 * with the constant byte @byte.
 *
 * Return: A pointer to the destination memory area @dest.
 */
char *_memset(char *dest, char byte, unsigned int count)
{
	unsigned int index;

	for (index = 0; index < count; index++)
		dest[index] = byte;

	return (dest);
}


/**
 * ffree - Frees the memory allocated for an array of strings.
 * @str_arr: Pointer to an array of strings.
 *
 * This function frees the memory allocated for each string in the array
 * and then frees the memory allocated for the array itself.
 */
void ffree(char **str_arr)
{
	char **temp = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);

	free(temp);
}

/**
 * _realloc - Reallocates memory for a block of memory.
 * @oldBlock: Pointer to the previously allocated memory block.
 * @oldSize: Size of the old allocated memory block.
 * @newSize: Size of the new memory block.
 *
 * This function changes the size of the memory block pointed to by oldBlock
 * to newSize bytes. The contents will be unchanged in the range from
 * the start of the block up to the minimum of the old and new sizes.
 * If the newSize is larger, the uninitialized memory will be left
 * with an indeterminate value.
 *
 * Return: If newSize is zero and oldBlock is not NULL, the function returns
 * a pointer to a newly allocated block or NULL on failure. If newSize
 * is zero and oldBlock is NULL, the function returns NULL. Otherwise,
 * it returns a pointer to the reallocated memory.
 */
void *_realloc(void *oldBlock, unsigned int oldSize, unsigned int newSize)
{
	char *newBlock;

	if (!oldBlock)
		return (malloc(newSize));

	if (!newSize)
		return (free(oldBlock), NULL);

	if (newSize == oldSize)
		return (oldBlock);

	newBlock = malloc(newSize);
	if (!newBlock)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newBlock[oldSize] = ((char *)oldBlock)[oldSize];
	free(oldBlock);
	return (newBlock);
}
