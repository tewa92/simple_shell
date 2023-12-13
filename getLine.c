#include "shell.h"

/**
 * input_buf - Reads input from the user into a buffer.
 * @inform: Pointer to the information structure.
 * @buff: Pointer to the buffer storing the input.
 * @leng: Pointer to the length of the buffer.
 * Return: The number of characters read or -1 on error.
 */
ssize_t input_buf(info_t *inform, char **buff, size_t *leng)
{
	ssize_t read_count = 0;
	size_t buff_length = 0;

	if (!*leng) /* If nothing left in the buffer, fill it */
	{
		/*bfree((void **)inform->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		read_count = getline(buff, &buff_length, stdin);
#else
		read_count = _getline(inform, buff, &buff_length);
#endif

		if (read_count > 0)
		{
			if ((*buff)[read_count - 1] == '\n')
			{
				/* Remove trailing newline */
				(*buff)[read_count - 1] = '\0';
				read_count--;
			}
			inform->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(inform, *buff, inform->histcount++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*leng = read_count;
				inform->cmd_buf = buff;
			}
		}
	}
	return (read_count);
}

/**
 * get_input - Retrieves input from the user, handling command chaining.
 * @inform: Pointer to the information structure.
 *
 * Return: The length of the current command or -1 on EOF.
 */
ssize_t get_input(info_t *inform)
{
	static char *chain_buffer; /* The ';' command chain buffer */
	static size_t chain_index, current_index, buffer_length;
	ssize_t read_length = 0;
	char **command_ptr = &(inform->arg), *command_position;

	_putchar(BUF_FLUSH);
	read_length = input_buf(inform, &chain_buffer, &buffer_length);

	if (read_length == -1) /* EOF */
		return (-1);

	if (buffer_length) /* Commands left in the chain buffer */
	{
		/* Initialize new iterator to current buffer position */
		current_index = chain_index;
		command_position = chain_buffer + chain_index; /* Get pointer for return */

		check_chain(inform, chain_buffer, &current_index,
				chain_index, buffer_length);
		while (current_index < buffer_length) /* Iterate to semicolon or end */
		{
			if (is_chain(inform, chain_buffer, &current_index))
				break;
			current_index++;
		}

		chain_index = current_index + 1; /* Increment past nulled ';'' */
		if (chain_index >= buffer_length) /* Reached end of buffer? */
		{
			chain_index = buffer_length = 0; /* Reset position and length */
			inform->cmd_buf_type = CMD_NORM;
		}

		/* Pass back pointer to current command position */
		*command_ptr = command_position;

		return (_strlen(command_position)); /* Return length of current command */
	}

	/* Not a chain, pass back buffer from input_buf() */
	*command_ptr = chain_buffer;

	return (read_length); /* Return length of buffer from input_buf() */
}


/**
 * read_buf - Reads data from a file descriptor into a buffer.
 * @inform: Pointer to the information structure.
 * @buff: Pointer to the buffer to store the data.
 * @j: Pointer to the variable indicating the amount of data read.
 *
 * Return: The number of bytes read or -1 on error.
 */
ssize_t read_buf(info_t *inform, char *buff, size_t *j)
{
	ssize_t read_count = 0;

	if (*j)
		return (0);

	read_count = read(inform->readfd, buff, READ_BUF_SIZE);
	if (read_count >= 0)
		*j = read_count;

	return (read_count);
}


/**
 * _getline - Gets the next line of input from STDIN.
 * @inform: Pointer to the information structure.
 * @potr: Address of pointer to buffer, preallocated or NULL.
 * @leng: Size of preallocated potr buffer if not NULL.
 *
 * Return: The length of the line read or -1 on error.
 */
int _getline(info_t *inform, char **potr, size_t *leng)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t c;
	ssize_t read = 0, h = 0;
	char *nd = NULL, *new_d = NULL, *end;

	nd = *potr;
	if (nd && leng)
		h = *leng;
	if (m == len)
		m = len = 0;

	read = read_buf(inform, buf, &len);
	if (read == -1 || (read == 0 && len == 0))
		return (-1);

	end = _strchr(buf + m, '\n');
	c = end ? 1 + (unsigned int)(end - buf) : len;
	new_d = _realloc(nd, h, h ? h + c : c + 1);
	if (!new_d) /* MALLOC FAILURE! */
		return (nd ? free(nd), -1 : -1);

	if (h)
		_strncat(new_d, buf + m, c - m);
	else
		_strncpy(new_d, buf + m, c - m + 1);

	h += c - m;
	m = c;
	nd = new_d;

	if (leng)
		*leng = h;
	*potr = nd;
	return (h);
}


/**
 * sigintHandler - Handles the SIGINT signal (Ctrl+C).
 * @sig_numb: Signal number (unused).
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
