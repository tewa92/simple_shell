#include "shell.h"

/**
 * _strcpy - Copies a string from source to destination.
 * @destination: Pointer to the destination string.
 * @source: Pointer to the source string.
 *
 * This function copies the content of the source string to the destination
 * string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcpy(char *destination, char *source)
{
  int index = 0;

  if (destination == source || source == 0)
    return (destination);
  while (source[index])
  {
    destination[index] = source[index];
    index++;
  }
  destination[index] = 0;
  return (destination);
}

/**
 * _strdup - Duplicates a string.
 * @input_str: Pointer to the string to be duplicated.
 *
 * This function duplicates the given string using dynamic memory allocation.
 *
 * Return: A pointer to the duplicated string, or NULL if memory
 *	allocation fails.
 */
char *_strdup(const char *input_str)
{
  int str_length = 0;
  char *result;

  if (input_str == NULL)
    return (NULL);
  while (*input_str++)
    str_length++;
  result = malloc(sizeof(char) * (str_length + 1));
  if (!result)
    return (NULL);
  for (str_length++; str_length--;)
    result[str_length] = *--input_str;
  return (result);
}


/**
 * _puts - Prints a string.
 * @output_string: Pointer to the string to be printed.
 *
 * This function prints the characters of the given string.
 */
void _puts(char *output_string)
{
  int index = 0;

  if (!output_string)
    return;
  while (output_string[index] != '\0')
  {
    _putchar(output_string[index]);
    index++;
  }
}


/**
 * _putchar - Writes a character to the output buffer.
 * @character: The character to be written.
 *
 * This function writes the given character to the output buffer.
 * If the buffer is full or a special flush character is encountered,
 * the buffer contents are flushed to the standard output.
 *
 * Return: Always returns 1.
 */
int _putchar(char character)
{
  static int buffer_index;
  static char buffer[WRITE_BUF_SIZE];

  if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
  {
    write(1, buffer, buffer_index);
    buffer_index = 0;
  }

  if (character != BUF_FLUSH)
    buffer[buffer_index++] = character;
  return (1);
}
