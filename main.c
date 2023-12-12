#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @ac: Number of command-line arguments.
 * @avec: Array of command-line argument strings.
 *
 * This function initializes the shell, opens a file descriptor if a filename
 * is provided as a command-line argument, populates the environment list,
 * reads the command history, and starts the shell.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int ac, char **avec)
{
	info_t inform[] = { INFO_INIT };
	int filedesc = 2; /* Default file descriptor for standard error */

	asm (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (filedesc)
			: "r" (filedesc)
			);

	if (ac == 2)
	{
		filedesc = open(avec[1], O_RDONLY);
		if (filedesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(avec[0]);
				_eputs(": 0: Can't open ");
				_eputs(avec[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inform->readfd = filedesc;
	}

	populate_env_list(inform);
	read_history(inform);
	hsh(inform, avec);

	return (EXIT_SUCCESS);
}
