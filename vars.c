#include "shell.h"

/**
 * is_chain - Checks for command chaining operators in the input buffer.
 * @information: Pointer to the information structure.
 * @buffer: The input buffer containing the command line.
 * @position: Pointer to the current position in the buffer.
 *
 * This function checks for command chaining operators (||, &&, ;) in the
 *	buffer and updates the information structure accordingly. It also
 *	modifies the buffer by replacing the operator with a null
 *	terminator if found.
 *
 * Return: 1 if a chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *information, char *buffer, size_t *position)
{
size_t index = *position;

  if (buffer[index] == '|' && buffer[index + 1] == '|')
  {
    buffer[index] = 0;
    index++;
    information->cmd_buf_type = CMD_OR;
  }
  else if (buffer[index] == '&' && buffer[index + 1] == '&')
  {
    buffer[index] = 0;
    index++;
    information->cmd_buf_type = CMD_AND;
  }
  else if (buffer[index] == ';') /* Found end of this command */
  {
    buffer[index] = 0; /* Replace semicolon with null */
    information->cmd_buf_type = CMD_CHAIN;
  }
  else
    return (0);

  *position = index;
return (1);
}

/**
* check_chain - Processes the command chaining condition based on the
*                           command buffer type in the information structure.
* @information: Pointer to the information structure.
* @buffer: The input buffer containing the command line.
* @position: Pointer to the current position in the buffer.
* @index: The loop index.
* @loop_length: The length of the loop.
*
* This function processes the command chaining condition based on the command
*	buffer type in the information structure. It modifies the buffer by
*	replacing characters with null terminators if the condition is met.
*/
void check_chain(info_t *information, char *buffer, size_t *position, size_t index, size_t loop_length)
{
  size_t loop_index = *position;

  if (information->cmd_buf_type == CMD_AND)
  {
    if (information->status)
    {
      buffer[index] = 0;
      loop_index = loop_length;
    }
  }
  if (information->cmd_buf_type == CMD_OR)
  {
    if (!information->status)
    {
      buffer[index] = 0;
      loop_index = loop_length;
    }
  }

  *position = loop_index;
}


/**
* replace_alias - Replaces the command with its alias if an alias is found.
* @information: Pointer to the information structure.
*
* This function attempts to replace the command in the information structure
*	with its alias if an alias is found. It iterates up to 10 times to
*	handle nested aliases.
* Return: 1 on success, 0 on failure.
*/
int replace_alias(info_t *information)
{
  int iteration;
  list_t *aliasNode;
  char *aliasValue;

  for (iteration = 0; iteration < 10; iteration++)
  {
    aliasNode = node_starts_with(information->alias, information->argv[0], '=');
    if (!aliasNode)
      return (0);
    free(information->argv[0]);
    aliasValue = _strchr(aliasNode->str, '=');
    if (!aliasValue)
      return (0);
    aliasValue = _strdup(aliasValue + 1);
    if (!aliasValue)
      return (0);
    information->argv[0] = aliasValue;
  }
  return (1);
}

/**
* replace_vars - Replaces variables in the command arguments.
* @information: Pointer to the information structure.
*
* This function iterates through the command arguments and replaces variables
*	with their corresponding values. It supports special
*	variables like $? and $$.
* Return: 0 on success.
*/
int replace_vars(info_t *information)
{
  int argIndex = 0;
  list_t *envNode;

  for (argIndex = 0; information->argv[argIndex]; argIndex++)
  {
    char *currentArg = information->argv[argIndex];
    if (currentArg[0] != '$' || !currentArg[1])
      continue;

    if (!_strcmp(currentArg, "$?"))
    {
      replace_string(&(information->argv[argIndex]),
        _strdup(convert_number(information->status, 10, 0)));
      continue;
    }

    if (!_strcmp(currentArg, "$$"))
    {
      replace_string(&(information->argv[argIndex]),
        _strdup(convert_number(getpid(), 10, 0)));
      continue;
    }

    envNode = node_starts_with(information->env, &(currentArg[1]), '=');
    if (envNode)
    {
      replace_string(&(information->argv[argIndex]),
        _strdup(_strchr(envNode->str, '=') + 1));
      continue;
    }

    replace_string(&(information->argv[argIndex]), _strdup(""));
  }

  return (0);
}

/**
* replace_string - Replaces a string with a new one, freeing the old string.
* @old_str: Pointer to the old string to be replaced.
* @new_str: Pointer to the new string.
*
* This function frees the memory allocated for the old string and assigns the
* new string to the provided pointer. Returns 1 on success.
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old_str, char *new_str)
{
  free(*old_str);
  *old_str = new_str;
  return (1);
}
