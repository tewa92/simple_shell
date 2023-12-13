#include "shell.h"

/**
 * _myexit - Function Handles the exit functionality by
 *	checking for an exit argument, converting it to an integer
 *	and updating the status and error number accordingly.
 * @inform: Pointer to a structure (inform_t) containing information
 *	(Assuming inform has fields like argv, status, err_num)
 * Return: 1 if an illegal number is encountered, -2 otherwise.
 */
int _myexit(info_t *inform)
{
	int exitcheck;
	/* If there is an exit argument */
	if (inform->argv[1])
	{
		/* Convert the exit argument to an integer */
		exitcheck = _erratoi(inform->argv[1]);
		/* If the conversion fails, set status, print an error, and return 1 */
		if (exitcheck == -1)
		{
			inform->status = 2;
			print_error(inform, "Illegal number: ");
			_eputs(inform->argv[1]);
			_eputchar('\n');
			return (1);
		}

		/* Update the error number with the converted exit argument */
		inform->err_num = _erratoi(inform->argv[1]);

		/* Return -2 to indicate successful exit handling */
		return (-2);
	}

	/**
	 * If no exit argument is provided, set the error
	 * number to -1 and return -2
	 */
	inform->err_num = -1;
	return (-2);
} /* End of _myexit function */

/**
 * _mycd - Function Implements the 'cd' command, allowing the user
 *	to change the current working directory.
 * @inform: Pointer to a structure (inform_t) containing
 *	information (Assuming inform has fields like argv,
 *	status, err_num)
 * Return: 0 on successful directory change, 1 on error.
 */
int _mycd(info_t *inform)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	/* Get the current working directory */
	s = getcwd(buffer, 1024);

	/**
	 * Print an error message if getcwd fails (TODO:
	 * Add a meaningful error message)
	 */
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	/* If no directory argument is provided */
	if (!inform->argv[1])
	{
	/* Get the HOME directory and change to it, or use "/" if HOME is not set */
		dir = _getenv(inform, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(inform, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	/* If the argument is "-", change to the previous working directory */
	else if (_strcmp(inform->argv[1], "-") == 0)
	{
	/* If OLDPWD is not set, print an error message */
		if (!_getenv(inform, "OLDPWD="))
		{
			_puts(s);
			_putschar('\n');
		return (1);
	}

	/* Print the previous working directory and change to it */
	_puts(_getenv(inform, "OLDPWD=")), _putchar('\n');
	chdir_ret = /* TODO: what should this be? */
		chdir((dir = _getenv(inform, "OLDPWD=")) ? dir : "/");
	}

	/* Change to the specified directory */

	else
		chdir_ret = chdir(inform->argv[1]);

	/* Handle errors if chdirect fails */
	if (chdir_ret == -1)

	{
		print_error(inform, "can't cd to ");
		_eputs(inform->argv[1]), _eputchar('\n');
	}
	else
	{
		/* Update the environment variables OLDPWD and PWD */
		_setenv(inform, "OLDPWD", _getenv(inform, "PWD="));
		_setenv(inform, "PWD", getcwd(buffer, 1024));
	}

	/* Return 0 on successful directory change, 1 on error */

	return (0);
} /* End of _mycd function */


/**
 * _myhelp - Function Displays assistance information, indicating
 * that the corresponding function
 *              has not been implemented yet.
 * @inform: Pointer to a structure (inform_t) containing information
 *             (Assuming inform has fields like argv, status, err_num)
 * Return: 0.
 */
int _myhelp(info_t *inform)
{
	char **arg_array;
	/* Assign the argv array to arg_array */
	arg_array = inform->argv;

	/**
	 * Display a message indicating that the function is not
	 * implemented yet
	 */
	_puts("Assistance request is functional, but function has not been work.\n");


	if (0)
		_puts(*arg_array); /* temp att_unused workaround */

	/* Return 0 */
	return (0);
} /* End of _myhelp function */
