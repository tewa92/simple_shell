#include "shell.h"

/**
 * _myhistory - Function Displays the command history
 * stored in the linked list.
 * @inform: Pointer to a structure (info_t) containing information
 *	(Assuming inform has a field named history which is a
 *	linked list of commands)
 * Return: 0.
 */
int _myhistory(info_t *inform)
{
	/* Print the command history stored in the linked list */
	print_list(inform->history);

	/* Return 0 */
	return (0);
} /* End of _myhistory function */


/**
 * unset_alias - Function Unsets an alias by removing it from
 *	the alias linked list.
 * @inform: Pointer to a structure (info_t) containing information
 *	(Assuming inform has a field named alias which is a
 *	linked list of aliases)
 * @str: The alias to be unset.
 * Return: 1 on failure (if '=' is not found in the alias),
 * otherwise returns the
 * result of the delete operation.
 */
int unset_alias(info_t *inform, char *str)
{
	char *k, f;
	int rete;

	/* Find the position of '=' in the alias */
	k = _strchr(str, '=');

	/* If '=' is not found, return 1 (failure) */

	if (!k)
		return (1);
	/**
	 * Save the character at position k and temporarily replace
	* it with null terminator
	*/
	f = *k;
	*k = 0;

	/* Delete the alias node at the specified index in the linked list */
	rete = delete_node_at_index(&(inform->alias),
			get_node_index(inform->alias, node_starts_with(inform->alias, str, -1)));

	/* Restore the character at position k */
	*k = f;

	/* Return the result of the delete operation */

	return (rete);
} /* End of unset_alias function */


/**
 * set_alias - Function Sets an alias by adding it to the alias
 *	linked list.
 * @inform: Pointer to a structure (info_t) containing information
 *	(Assuming inform has a field named alias which is a
 *	linked list of aliases)
 * @str: The alias to be set.
 * Return: 1 on failure (if '=' is not found in the alias),
 *	0 otherwise
 */
int set_alias(info_t *inform, char *str)
{
	char *k;

	/* Find the position of '=' in the alias */
	k = _strchr(str, '=');

	/* If '=' is not found, return 1 (failure) */
	if (!k)
		return (1);
	/**If the character immediately after '=' is null, unset the alias*/

	if (!*++k)
		return (unset_alias(inform, str));
	unset_alias(inform, str);

	/**
	 * Return 1 on failure, 0 otherwise
	 *	(add_node_end returns NULL on success)
	 */
	return (add_node_end(&(inform->alias), str, 0) == NULL);
} /* End of set_alias function */

/**
 * print_alias - Function Prints the contents of an alias
 *	node in the specified format.
 * @node: Pointer to a node in the alias linked list
 *	(Assuming it's a linked list of aliases).
 * Return: 0 on success, 1 if the node is NULL.
 */
int print_alias(list_t *node)
{
	char *k = NULL, *i = NULL;

	/* Check if the alias_node is not NULL */
	if (node)
	{
		/* Find the position of '=' in the alias */
		k = _strchr(node->str, '=');

		/* Loop through the characters in the alias up to and including '=' */
		for (i = node->str; i <= k; i++)
			_putchar(*i);

		/* Print a single quote after the '=' */
		_putchar('\'');

		/* Print the characters after '=' */
		_puts(k + 1);

		/* Print a newline character */
		_puts("'\n");

		/* Return 0 to indicate success */
		return (0);
	}
	/* Return 1 if the alias_node is NULL */
	return (1);
} /* End of print_alias function */


/**
 * _myalias - Function Handles the 'alias' command, allowing
 *	users to view, set, and unset aliases.
 * @inform: Pointer to a structure (info_t) containing information
 *	(Assuming inform has fields like argc, argv, and alias
 *	which is a linked list of aliases)
 * Return: 0.
 */
int _myalias(info_t *inform)
{
	int k = 0;
	char *e = NULL;
	list_t *node = NULL;

	/* If 'alias' command is used without arguments, print all aliases */
	if (inform->argc == 1)
	{
		node = inform->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	/* Loop through the arguments and either set or print aliases */
	for (k = 1; inform->argv[k]; k++)
	{
		/* Find the position of '=' in the argument */
		e = _strchr(inform->argv[k], '=');

		/* If '=' is found, set the alias */
		if (e)
			set_alias(inform, inform->argv[k]);

		/* If '=' is not found, print the aliases that match the prefix */

		else
			print_alias(node_starts_with(inform->alias, inform->argv[k], '='));
	}

	/* Return 0 */
	return (0);
} /* End of _myalias function */
