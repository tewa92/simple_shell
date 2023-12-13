#include "shell.h"

/**
 * clear_info - Resets information structure members to NULL or 0.
 * @inform: Pointer to the information structure.
 */
void clear_info(info_t *inform)
{
	inform->arg = NULL;
	inform->argv = NULL;
	inform->path = NULL;
	inform->argc = 0;
} /* End of clear_info function */


/**
 * set_info - Sets information structure members based on command
 * line arguments.
 * @inform: Pointer to the information structure.
 * @avec: Array of command line arguments.
 */
void set_info(info_t *inform, char **avec)
{
	int m = 0;

	inform->fname = avec[0];

	if (inform->arg)
	{
		inform->argv = strtow(inform->arg, " \t");

		if (!inform->argv)
		{
			inform->argv = malloc(sizeof(char *) * 2);

			if (inform->argv)
			{
				inform->argv[0] = _strdup(inform->arg);
				inform->argv[1] = NULL;
			}
		}

		for (m = 0; inform->argv && inform->argv[m]; m++)
			;

		inform->argc = m;

		replace_alias(inform);
		replace_vars(inform);
	}
} /* End of set_info function */


/**
* free_info - Frees memory allocated for information structure members.
* @inform: Pointer to the information structure.
* @all: Flag indicating whether to free all associated memory.
*/
void free_info(info_t *inform, int all)
{
	ffree(inform->argv);
	inform->argv = NULL;
	inform->path = NULL;

	if (all)
	{
		if (!inform->cmd_buf)
			free(inform->arg);
		if (inform->env)
			free_list(&(inform->env));
		if (inform->history)
			free_list(&(inform->history));
		if (inform->alias)
			free_list(&(inform->alias));
		ffree(inform->environ);
		inform->environ = NULL;
		bfree((void **)inform->cmd_buf);

		if (inform->readfd > 2)
			close(inform->readfd);

		_putchar(BUF_FLUSH);
	}
} /* End of free_info function */
