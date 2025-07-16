#include "shell.h"

/**
 * get_line - Reads a line from a file stream.
 * @lineptr: Pointer to the buffer storing the line.
 * @n: Pointer to the size of the buffer.
 * @stream: The file stream to read from.
 *
 * Return: The number of characters read.
 */

ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer, *temp;
	int buffer_size, index, c;

	buffer = NULL;
	temp = NULL;
	buffer_size = 80;
	index = 0;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	buffer = (char *)malloc(buffer_size);
	if (buffer == NULL)
		return (-1);
	while ((c = fgetc(stream)) != EOF)
	{
		if (index >= buffer_size - 1)
		{
			buffer_size *= 2;
			temp = realloc(buffer, buffer_size);
			if (temp == NULL)
			{
				free(buffer);
				return (-1);
			}
			buffer = temp;
		}
		buffer[index++] = c;
		if (c == '\n')
			break;
	}
	if (index == 0)
	{
		free(buffer);
		return (-1);
	}

	buffer[index] = '\0';
	*lineptr = buffer;
	*n = buffer_size;

	return (index);
}
