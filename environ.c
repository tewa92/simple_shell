#include "shell.h"

/**
 * _myenv - Prints the environment variables stored in the linked list.
 * @inform: Pointer to a structure (info_t) containing information
 *           (Assuming inform has a field named env which is
 *           a linked list of environment variables)
 * Return: Returns 0.
 */
int _myenv(info_t *inform)
{
	/* Print the environment variables stored in the linked list */
	print_list_str(inform->env);

	/* Return 0 */
	return (0);

} /* End of _myenv function */


/**
 * _getenv - Searches for an environment variable with a
 *	specified name in a linked list.
 * @inform: Pointer to a structure (info_t) containing information
 *           (Assuming inform has a field named env which is
 *           a linked list of environment variables)
 * @names: Name of the environment variable to search for.
 * Return: Returns a pointer to the value of the environment
 *	variable if found, or NULL if not found.
 */
char *_getenv(info_t *inform, const char *names)
{
	list_t *node = inform->env;
	char *k;

	/* Iterate through the linked list of environment variables */
	while (node)
	{
		/* Check if the value of the current node starts with the specified name */
		k = starts_with(node->str, names);

		/* If a match is found and the value is not empty, return the value */
		if (k && *k)
			return (k);

		/* Move to the next node in the linked list */
		node = node->next;
	}

	/**
	 * Return NULL if the environment variable with the
	 * specified name is not found
	 */

	return (NULL);
} /* End of _getenv function */


/**
 * _mysetenv - Sets or updates an environment variable with a
 *	specified name and value.
 * @inform: Pointer to a structure (info_t) containing information
 *           (Assuming inform has fields like argc, argv, and env
 *           which is a linked list of environment variables)
 * Return: Returns 0 on success, 1 on failure.
 */
int _mysetenv(info_t *inform)
{
	/* Check if the number of arguments is not equal to 3 */
	if (inform->argc != 3)
	{
		/*
		 * Print an error message for an invalid number of arguments.
		 */
		_eputs("Invalid number of arguments\n");

		/*Return 1 to indicate failure.*/
		return (1);
	}

	/*
	 * Attempt to set or update the environment variable.
	 * Return 0 on success, 1 on failure.
	 */

	if (_setenv(inform, inform->argv[1], inform->argv[2]))
		return (0);

	/*Return 1 on failure.*/
	return (1);
} /* End of _mysetenv function */


/**
 * _myunsetenv - Removes one or more environment variables based
 *	on the specified names.
 * @inform: Pointer to a structure (info_t) containing information
 *           (Assuming inform has fields like argc, argv, and env
 *           which is a linked list of environment variables)
 * Return: Returns 0 on success, 1 on failure.
 */
int _myunsetenv(info_t *inform)
{
	int o;

	/*
	 * Check if the number of arguments is equal to 1,
	 *	indicating not enough arguments.
	 * Print an error message and return 1 on failure.
	 */
	if (inform->argc == 1)
	{
		_eputs("Not enough arguments.\n");
		return (1);
	}

	/*
	 * Loop through the arguments and unset the corresponding
	 *	environment variables
	 */

	for (o = 1; o <= inform->argc; o++)
		_unsetenv(inform, inform->argv[o]);

	/* Return 0 on success.*/
	return (0);
} /* End of _myunsetenv function */


/**
 * populate_env_list - Populates the environment variable linked
 *	list using the 'environ' array.
 * @inform: Pointer to a structure (info_t) containing information
 *           (Assuming inform has fields like env which is
 *           a linked list of environment variables)
 * Return: Returns 0 on success.
 */
int populate_env_list(info_t *inform)
{
	list_t *node = NULL;
	size_t o;

	/*
	 * Iterate through the 'environ' array and add each environment
	 *	variable to the linked list.
	 */
	for (o = 0; environ[o]; o++)
		add_node_end(&node, environ[o], 0);

	/*
	 * Set the 'env' field in the inform structure to the populated
	 *	linked list.
	 * Return 0 on success.
	 */
	inform->env = node;
	return (0);
} /* End of populate_env_list function */
