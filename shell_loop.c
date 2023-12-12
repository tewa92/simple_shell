#include "shell.h"

/**
 * hsh - Main function for the shell.
 * @inform: Pointer to the information struct.
 * @avec: Array of strings representing command-line arguments.
 *
 * This function serves as the main entry point for the shell. It runs
 *	the shell
 * in interactive mode or processes commands from a script. It repeatedly
 * clears the information, prompts for input, gets user input, sets up the
 * information struct, finds and executes built-in commands or external
 * commands, and handles the exit conditions.
 *
 * Return: The exit status or error code.
 */
int hsh(info_t *inform, char **avec)
{
ssize_t readResult = 0;
int builtinResult = 0;

while (readResult != -1 && builtinResult != -2)
{
clear_info(inform);

if (interactive(inform))
_puts("$ ");

_eputchar(BUF_FLUSH);
readResult = get_input(inform);

if (readResult != -1)
{
set_info(inform, avec);
builtinResult = find_builtin(inform);

if (builtinResult == -1)
find_cmd(inform);
}
else if (interactive(inform))
_putchar('\n');

free_info(inform, 0);
}

write_history(inform);
free_info(inform, 1);

if (!interactive(inform) && inform->status)
exit(inform->status);

if (builtinResult == -2)
{
if (inform->err_num == -1)
exit(inform->status);

exit(inform->err_num);
}

return (builtinResult);
}

/**
* find_builtin - Finds and executes a built-in command.
* @inform: Pointer to the information struct.
*
* This function iterates through the built-in command table and compares
* the given command with each entry. If a match is found, the corresponding
* built-in function is executed, and the function returns the result.
*
* Return: The result of the executed built-in command or -1 if no
*	match is found.
*/
int find_builtin(info_t *inform)
{
int index, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}
};

for (index = 0; builtintbl[index].type; index++)
{
if (_strcmp(inform->argv[0], builtintbl[index].type) == 0)
{
inform->line_count++;
built_in_ret = builtintbl[index].func(inform);
break;
}
}

return (built_in_ret);
}

/**
* find_cmd - Searches for the command in the PATH and executes it.
* @inform: Pointer to the information struct.
*
* This function sets the path to the command and checks for the existence of
* the command in the PATH. If found, it updates the path in the information
* struct and forks a new process to execute the command. If not found,
*	it checks
* if the command is an absolute path or part of a built-in command. If neither,
* an error is printed.
*/
void find_cmd(info_t *inform)
{
char *command_path = NULL;
int argument_count = 0;

inform->path = inform->argv[0];

if (inform->linecount_flag == 1)
{
inform->line_count++;
inform->linecount_flag = 0;
}

for (int index = 0; inform->arg[index]; index++)
{
if (!is_delim(inform->arg[index], " \t\n"))
argument_count++;
}

if (!argument_count)
return;

command_path = find_command_path(inform, _getenv(inform, "PATH="), inform->argv[0]);

if (command_path)
{
inform->path = command_path;
fork_and_execute_command(inform);
}
else
{
if ((interactive(inform) || _getenv(inform, "PATH=") || inform->argv[0][0] == '/') &&
is_cmd(inform, inform->argv[0]))
{
fork_and_execute_command(inform);
}
else if (*(inform->arg) != '\n')
{
inform->status = 127;
print_error(inform, "not found\n");
}
}
}

/**
* fork_cmd - Forks a new process and executes the command.
* @info: Pointer to the information struct.
*
* This function forks a new process to execute the command. If the fork is
* unsuccessful, an error is printed. In the child process, it attempts to
* execute the command using execve. If execution fails, appropriate error
* handling is performed. In the parent process, it waits for the child process
* to complete and updates the status in the information struct.
*/
void fork_cmd(info_t *info)
{
pid_t child_process_id;

child_process_id = fork();

if (child_process_id == -1)
{
/* TODO: Implement error handling function */
perror("Error:");
return;
}

if (child_process_id == 0)
{
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);

if (errno == EACCES)
exit(126);

exit(1);
}
/* TODO: Implement error handling function */
}
else
{
wait(&(info->status));

if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);

if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
