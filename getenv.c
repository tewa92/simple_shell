#include "shell.h"

/**
 * get_environ - Retrieves the environment variables as an array of strings.
 * @inform: Pointer to the information structure.
 * Return: Pointer to the array of environment variables.
 */
char **get_environ(info_t *inform)
{
	/**
	 * If the environment variables are not present or have changed,
	 * convert the linked list of environment variables to an array of strings.
	 * Update the information structure accordingly.
	 */
	if (!inform->environ || inform->env_changed)
	{
		inform->environ = list_to_strings(inform->env);
		inform->env_changed = 0;
	}

	/* Return a pointer to the array of environment variables. */
	return (inform->environ);
} /* End of get_environ function */


/**
* _unsetenv - Removes an environment variable.
* @inform: Pointer to the information structure.
* @vari: Pointer to the name of the environment variable to remove.
* Return: 1 if the variable is successfully removed, 0 otherwise.
*/
int _unsetenv(info_t *inform, char *vari)
{
	list_t *node = inform->env;
	size_t o = 0;
	char *h;

	/**
	* Return 0 if the linked list of environment variables or the
	* variable name is not present.
	*/
	if (!node || !vari)
		return (0);

	/**
	* Iterate through the linked list of environment variables.
	* If a variable with the specified name is found, remove it from the list.
	* Update the environment change flag accordingly.
	*/
	while (node)
	{
		h = starts_with(node->str, vari);
		if (h && *h == '=')
		{
			inform->env_changed = delete_node_at_index(&(inform->env), o);
			o = 0;
			node = inform->env;
			continue;
		}
		node = node->next;
		o++;
	}

	/**
	* Return the environment change flag
	*	(1 if a variable was removed, 0 otherwise).
	*/
	return (inform->env_changed);
} /* End of _unsetenv function */


/**
* _setenv - Sets the value of an environment variable or adds a new variable.
* @inform: Pointer to the information structure.
* @vari: Pointer to the name of the environment variable.
* @amount: Pointer to the value to set for the environment variable.
* Return: 0 on success, 1 on failure.
*/
int _setenv(info_t *inform, char *vari, char *amount)
{
	char *buff = NULL;
	list_t *node;
	char *b;

	/* Return 1 if the variable name or value is not present. */
	if (!vari || !amount)
		return (1);

	/* Allocate memory for the new environment variable string. */
	buff = malloc(_strlen(vari) + _strlen(amount) + 2);
	if (!buff)
		return (1);

	/* Create the new environment variable string with the format "name=value". */
	_strcpy(buff, vari);
	_strcat(buff, "=");
	_strcat(buff, amount);

	/* Iterate through the linked list of environment variables. */
	node = inform->env;
	while (node)
	{
		b = starts_with(node->str, vari);
		if (b && *b == '=')
		{
			/* If the variable already exists, update its value. */
			free(node->str);
			node->str = buff;
			inform->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	/* If the variable does not exist, add it to the end of the list. */
	add_node_end(&(inform->env), buff, 0);
	free(buff);
	inform->env_changed = 1;
	return (0);
} /* End of _setenv function */
