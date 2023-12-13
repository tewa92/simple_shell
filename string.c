#include "shell.h"

/**
 * _strlen - Computes the length of a string.
 * @str: Pointer to the string.
 *
 * This function calculates the length of the input string by iterating
 * through each character until the null terminator is encountered. If the
 * input pointer is NULL, it returns 0.
 *
 * Return: Length of the string.
 */
int _strlen(char *str)
{
  int length = 0;

  if (!str)
    return (0);

  while (*str++)
    length++;

  return (length);
}


/**
 * _strcmp - Compares two strings.
 * @str1: Pointer to the first string.
 * @str2: Pointer to the second string.
 *
 * This function compares two strings character by character. It returns
 * an integer less than, equal to, or greater than zero if the first string
 * is found to be less than, equal to, or greater than the second string.
 *
 * Return: Negative value if str1 is less than str2,
 *         0 if str1 is equal to str2,
 *         Positive value if str1 is greater than str2.
 */
int _strcmp(char *str1, char *str2)
{
  while (*str1 && *str2)
  {
    if (*str1 != *str2)
      return (*str1 - *str2);
    str1++;
    str2++;
  }

  if (*str1 == *str2)
    return (0);
  else
    return (*str1 < *str2 ? -1 : 1);
}


/**
 * starts_with - Finds a prefix in a string.
 * @str: Pointer to the string to search.
 * @prefix: Pointer to the prefix to find.
 *
 * This function checks if the given string starts with the specified prefix.
 * If found, it returns a pointer to the character after the prefix; otherwise,
 * it returns NULL.
 *
 * Return: A pointer to the character after the prefix if found,
 *	NULL otherwise.
 */
char *starts_with(const char *str, const char *prefix)
{
  while (*prefix)
    if (*prefix++ != *str++)
      return (NULL);
  return ((char *)str);
}

/**
 * _strcat - Concatenates two strings.
 * @destination: Pointer to the destination string.
 * @source: Pointer to the source string.
 *
 * This function appends the content of the source string to the destination
 * string.
 *
 * Return: A pointer to the destination string.
 */
char *_strcat(char *destination, char *source)
{
  char *result = destination;

  while (*destination)
    destination++;
  while (*source)
    *destination++ = *source++;
  *destination = *source;

  return (result);
}
