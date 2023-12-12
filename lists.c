#include "shell.h"

/**
 * add_node - Creates and adds a new node at the beginning of a linked list.
 * @list_head: Pointer to the head of the linked list.
 * @data_str: String to be stored in the new node.
 * @data_num: Integer value to be stored in the new node.
 *
 * Return: A pointer to the newly created node.
 */
list_t *add_node(list_t **list_head, const char *data_str, int data_num)
{
	list_t *new_entry;

	if (!list_head)
		return (NULL);

	new_entry = malloc(sizeof(list_t));
	if (!new_entry)
		return (NULL);

	_memset((void *)new_entry, 0, sizeof(list_t));
	new_entry->num = data_num;

	if (data_str)
	{
		new_entry->str = _strdup(data_str);
		if (!new_entry->str)
		{
			free(new_entry);
			return (NULL);
		}
	}

	new_entry->next = *list_head;
	*list_head = new_entry;

	return (new_entry);
}

/**
 * add_node_end - Creates and adds a new node at the end of a linked list.
 * @list_head: Pointer to the head of the linked list.
 * @data_str: String to be stored in the new node.
 * @data_num: Integer value to be stored in the new node.
 *
 * Return: A pointer to the newly created node.
 */
list_t *add_node_end(list_t **list_head, const char *data_str, int data_num)
{
	list_t *new_entry, *current_node;

	if (!list_head)
		return (NULL);

	current_node = *list_head;
	new_entry = malloc(sizeof(list_t));
	if (!new_entry)
		return (NULL);

	_memset((void *)new_entry, 0, sizeof(list_t));
	new_entry->num = data_num;

	if (data_str)
	{
		new_entry->str = _strdup(data_str);
		if (!new_entry->str)
		{
			free(new_entry);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_entry;
	}
	else
	{
		*list_head = new_entry;
	}

	return (new_entry);
}

/**
 * print_list_str - Prints the strings stored in a linked list.
 * @f: Pointer to the head of the linked list.
 *
 * Return: The number of nodes in the list.
 */
size_t print_list_str(const list_t *f)
{
	size_t a = 0;

	while (f)
	{
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		a++;
	}

	return (a);
}


/**
 * delete_node_at_index - Deletes a node at a given index in a linked list.
 * @list_head: Pointer to the head of the linked list.
 * @target_index: Index of the node to be deleted.
 *
 * Return: 1 if successful, 0 otherwise.
 */
int delete_node_at_index(list_t **list_head, unsigned int target_index)
{
	list_t *current, *previous;
	unsigned int a = 0;

	if (!list_head || !*list_head)
		return (0);

	if (!target_index)
	{
		current = *list_head;
		*list_head = (*list_head)->next;
		free(current->str);
		free(current);
		return (1);
	}

	current = *list_head;
	while (current)
	{
		if (a == target_index)
		{
			previous->next = current->next;
			free(current->str);
			free(current);
			return (1);
		}
		a++;
		previous = current;
		current = current->next;
	}

	return (0);
}


/**
 * free_list - Frees a linked list and its nodes.
 * @list_head: Pointer to the head of the linked list.
 *
 * This function frees the memory allocated for each node in the linked list
 * and sets the head pointer to NULL.
 */
void free_list(list_t **list_head)
{
	list_t *current, *next_node, *list_start;

	if (!list_head || !*list_head)
		return;

	list_start = *list_head;
	current = list_start;

	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}

	*list_head = NULL;
}
