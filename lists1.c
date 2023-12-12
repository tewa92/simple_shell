#include "shell.h"

/**
 * list_len - Calculates the number of elements in a linked list.
 * @head: Pointer to the head of the linked list.
 *
 * This function traverses the linked list and counts the number of elements.
 *
 * Return: The number of elements in the linked list.
 */
size_t list_len(const list_t *head)
{
	size_t a = 0;

	while (head)
	{

		head = head->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings.
 * @list_head: Pointer to the head of the linked list.
 *
 * This function creates an array of strings from the linked list of strings.
 * It allocates memory for each string and the array itself.
 *
 * Return: An array of strings or NULL if memory allocation fails.
 */
char **list_to_strings(list_t *list_head)
{
	list_t *current_node = list_head;
	size_t a = list_len(list_head), h;
	char **strings;
	char *str;

	if (!list_head || !a)
		return (NULL);

	strings = malloc(sizeof(char *) * (a + 1));
	if (!strings)
		return (NULL);

	for (a = 0; current_node; current_node = current_node->next, a++)
	{
		str = malloc(_strlen(current_node->str) + 1);
		if (!str)
		{
			for (h = 0; h < a; h++)
				free(strings[h]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, current_node->str);
		strings[a] = str;
	}

	strings[a] = NULL;
	return (strings);
}


/**
 * print_list - Prints the elements of a linked list.
 * @list_head: Pointer to the head of the linked list.
 *
 * This function prints the elements of a linked list, including
 * the node numbers and strings.
 *
 * Return: The number of nodes in the linked list.
 */
size_t print_list(const list_t *list_head)
{
	size_t a = 0;

	while (list_head)
	{
		_puts(convert_number(list_head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(list_head->str ? list_head->str : "(nil)");
		_puts("\n");
		list_head = list_head->next;
		a++;
	}

	return (a);
}

/**
 * node_starts_with - Finds a node whose string starts with a
 *	given prefix and optional character.
 * @list_node: Pointer to the head of the linked list.
 * @search_prefix: Prefix to search for at the beginning of the strings.
 * @search_char: Optional character to check for after the prefix.
 *
 * This function searches for a node in a linked list whose string starts
 * with a given prefix and optional character. If found, it returns the node;
 * otherwise, it returns NULL.
 *
 * Return: Pointer to the first matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *list_node, char *search_prefix, char search_char)
{
	char *result_str = NULL;

	while (list_node)
	{
		result_str = starts_with(list_node->str, search_prefix);
		if (result_str && ((search_char == -1) || (*result_str == search_char)))
			return (list_node);
		list_node = list_node->next;
	}

	return (NULL);
}


/**
 * get_node_index - Gets the index of a node in a linked list.
 * @list_head: Pointer to the head of the linked list.
 * @target_node: Pointer to the node whose index is to be found.
 *
 * This function traverses a linked list to find the index of a specific node.
 *
 * Return: The index of the target node, or -1 if the node is not found.
 */
ssize_t get_node_index(list_t *list_head, list_t *target_node)
{
	size_t index = 0;

	while (list_head)
	{
		if (list_head == target_node)
			return (index);
		list_head = list_head->next;
		index++;
	}

	return (-1);
}
