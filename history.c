#include "shell.h"

/**
 * get_history_file - Constructs the full path of the history file.
 * @inform: Pointer to the information structure.
 *
 * Return: A pointer to the allocated buffer containing the history file path,
 *         or NULL on failure.
 */
char *get_history_file(info_t *inform)
{
	char *buff, *dire;

	dire = _getenv(inform, "HOME=");
	if (!dire)
		return (NULL);

	buff = malloc(sizeof(char) * (_strlen(dire) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);

	buff[0] = 0;
	_strcpy(buff, dire);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);

	return (buff);
}


/**
 * write_history - Writes the command history to a file.
 * @inform: Pointer to the information structure.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(info_t *inform)
{
	ssize_t filedesc;
	char *filename = get_history_file(inform);
	list_t *alias_node = NULL;

	if (!filename)
		return (-1);

	filedesc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (filedesc == -1)
		return (-1);

	for (alias_node = inform->history; alias_node; alias_node = alias_node->next)
	{
		_putsfd(alias_node->str, filedesc);
		_putfd('\n', filedesc);
	}

	_putfd(BUF_FLUSH, filedesc);
	close(filedesc);

	return (1);
}


/**
 * read_history - Reads command history from a file into the program's history.
 * @inform: Pointer to the information structure.
 *
 * Return: The number of lines read from history.
 */
int read_history(info_t *inform)
{
	int j, last = 0, linecount = 0;
	ssize_t filedesc, readleng, filesize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(inform);

	if (!filename)
		return (0);

	filedesc = open(filename, O_RDONLY);
	free(filename);

	if (filedesc == -1)
		return (0);

	if (!fstat(filedesc, &st))
		filesize = st.st_size;

	if (filesize < 2)
		return (0);

	buff = malloc(sizeof(char) * (filesize + 1));

	if (!buff)
		return (0);

	readleng = read(filedesc, buff, filesize);
	buff[filesize] = 0;

	if (readleng <= 0)
		return (free(buff), 0);

	close(filedesc);

	for (j = 0; j < filesize; j++)
	{
		if (buff[j] == '\n')
		{
			buff[j] = 0;
			build_history_list(inform, buff + last, linecount++);
			last = j + 1;
		}
	}

	if (last != j)
		build_history_list(inform, buff + last, linecount++);

	free(buff);
	inform->histcount = linecount;

	while (inform->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inform->history), 0);

	renumber_history(inform);
	return (inform->histcount);
}


/**
 * build_history_list - Builds a history list by adding a new node.
 * @inform: Pointer to the information structure.
 * @buff: The command to be added to the history list.
 * @linecount: The line count associated with the command.
 *
 * Return: Always 0.
 */
int build_history_list(info_t *inform, char *buff, int linecount)
{
	list_t *alias_node = NULL;

	if (inform->history)
		alias_node = inform->history;

	add_node_end(&alias_node, buff, linecount);

	if (!inform->history)
		inform->history = alias_node;

	return (0);
}


/**
 * renumber_history - Renumber the history list nodes.
 * @inform: Pointer to the information structure.
 *
 * Return: The updated history count.
 */
int renumber_history(info_t *inform)
{
	list_t *alias_node = inform->history;
	int linecount = 0;

	while (alias_node)
	{
		alias_node->num = linecount++;
		alias_node = alias_node->next;
	}

	return (inform->histcount = linecount);
}
