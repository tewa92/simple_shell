#include "shell.h"

/**
 * strtow - Splits a string into an array of words based on delimiters.
 * @str: The input string to be split.
 * @delimiters: The string containing delimiter characters.
 *
 * This function splits the input string into an array of words using the
 * specified delimiters. It dynamically allocates memory for the array.
 *
 * Return: If successful, returns the array of strings. Otherwise,
 *	returns NULL.
 */
char **strtow(char *str, char *delimiters)
{
	int idx, word_idx, char_idx, copy_idx, num_words = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (idx = 0; str[idx] != '\0'; idx++)
		if (!is_delim(str[idx], delimiters) && (is_delim(str[idx + 1],
						delimiters) || !str[idx + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);
	for (idx = 0, word_idx = 0; word_idx < num_words; word_idx++)
	{
		while (is_delim(str[idx], delimiters))
			idx++;
		char_idx = 0;
		while (!is_delim(str[idx + char_idx], delimiters) && str[idx + char_idx])
			char_idx++;
		result[word_idx] = malloc((char_idx + 1) * sizeof(char));
			if (!result[word_idx])
			{
				for (copy_idx = 0; copy_idx < word_idx; copy_idx++)
					free(result[copy_idx]);
				free(result);
				return (NULL);
			}
		for (copy_idx = 0; copy_idx < char_idx; copy_idx++)
			result[word_idx][copy_idx] = str[idx++];
		result[word_idx][copy_idx] = 0;
	}
	result[word_idx] = NULL;
	return (result);
}

/**
 * strtow2 - Splits a string into an array of words based on a delimiter.
 * @str: The input string to be split.
 * @delimiter: The delimiter character used for splitting.
 *
 * This function splits the input string into an array of words using the
 * specified delimiter. It dynamically allocates memory for the array.
 *
 * Return: If successful, returns the array of strings.
 *	Otherwise, returns NULL.
 */
char **strtow2(char *str, char delimiter)
{
	int idx, word_idx, char_idx, copy_idx, num_words = 0;
	char **result;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (idx = 0; str[idx] != '\0'; idx++)
		if ((str[idx] != delimiter && str[idx + 1] == delimiter) ||
				(str[idx] != delimiter && !str[idx + 1]) || str[idx + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	result = malloc((1 + num_words) * sizeof(char *));
	if (!result)
		return (NULL);

	for (idx = 0, word_idx = 0; word_idx < num_words; word_idx++)
	{
		while (str[idx] == delimiter && str[idx] != delimiter)
			idx++;
		char_idx = 0;
		while (str[idx + char_idx] != delimiter && str[idx + char_idx]
				&& str[idx + char_idx] != delimiter)
			char_idx++;
		result[word_idx] = malloc((char_idx + 1) * sizeof(char));
		if (!result[word_idx])
		{
			for (copy_idx = 0; copy_idx < word_idx; copy_idx++)
				free(result[copy_idx]);
			free(result);
			return (NULL);
		}
		for (copy_idx = 0; copy_idx < char_idx; copy_idx++)
			result[word_idx][copy_idx] = str[idx++];
		result[word_idx][copy_idx] = 0;
	}
	result[word_idx] = NULL;
	return (result);
}
