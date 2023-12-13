#include "shell.h"

/**
 * is_cmd - Checks if the given file path corresponds to a regular file.
 * @inform: Pointer to the information structure.
 * @file_path: Path to be checked.
 *
 * This function checks if the provided file path corresponds to
 *	a regular file.
 *
 * Return: 1 if the file path is a regular file, 0 otherwise.
 */
int is_cmd(info_t *inform, char *file_path)
{
	struct stat st;

	(void)inform;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates a portion of a string based on start an
 *	 stop indices.
 * @
 * @source_str: Source string to duplicate from.
 * @start_index: Start index for duplication.
 * @stop_index: Stop index for duplication.
 *
 * This function duplicates a portion of a string based on start
 *	and stop indices.
 *
 * Return: A pointer to the duplicated substring.
 */
char *dup_chars(char *source_str, int start_index, int stop_index)
{
	static char buffer[1024];
	int index_buffer = 0, source_index = 0;

	for (index_buffer = 0, source_index = start_index;
			source_index < stop_index; source_index++)
	{
		if (source_str[source_index] != ':')
			buffer[index_buffer++] = source_str[source_index];
	}

	buffer[index_buffer] = '\0';
	return (buffer);
}

/**
 * find_path - Finds the full path of a command in the given path string.
 * @data: Pointer to the info_t struct.
 * @path_str: Path string containing directories separated by ':'.
 * @command: The command to find.
 *
 * This function searches for the full path of a command in the
 *	given path string.
 * If the command is found, the full path is returned; otherwise, returns NULL.
 *
 * Return: A pointer to the full path of the command or NULL if not found.
 */
char *find_path(info_t *data, char *path_str, char *command)
{
	int index = 0, current_pos = 0;
	char *full_path;

	if (!path_str)
		return (NULL);

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(data, command))
			return (command);
	}

	while (1)
	{
		if (!path_str[index] || path_str[index] == ':')
		{
			full_path = dup_chars(path_str, current_pos, index);
			if (!*full_path)
				_strcat(full_path, command);
			else
			{
				_strcat(full_path, "/");
				_strcat(full_path, command);
			}

			if (is_cmd(data, full_path))
				return (full_path);

			if (!path_str[index])
				break;

			current_pos = index;
		}
		index++;
	}

	return (NULL);
}
